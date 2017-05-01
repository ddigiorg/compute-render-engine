// =========
// retina.cl
// =========

const sampler_t sampler = CLK_NORMALIZED_COORDS_FALSE | CLK_ADDRESS_CLAMP_TO_EDGE | CLK_FILTER_NEAREST;

__kernel void getRetinaOutput(__read_only image2d_t Tex2D_input, __write_only image2d_t Tex2D_retinaBW)
{
	int2 gXY;            // ganglion cell coordinates
	int2 gSizeXY;        // ganglion cell total amount in X and Y
	float gBias = 0.5f;  // ganglion cell bias
	float gBW;           // ganglion cell black vs white
	float gRG;           // ganglion cell red vs green
//	float gYB;           // ganglion cell yellow vs blue
	int2 rXY;            // receptor cell coordinates
	float4 rColor;       // receptor cell input color
	float rLuminance;    // receptor cell input luminance
	int rStartX = -2;    // receptor cell X start coordinate
	int rStartY = -2;    // receptor cell Y start coordinate
	int rEndX = 2;       // receptor cell X end coordinate
	int rEndY = 2;       // receptor cell Y end coordinate
	float rCW = 1.0f;    // receptor cell on-center weight

	// receptor cell off-surround weight
	float rSW = -1.0f/((rEndX - rStartX + 1) * (rEndY - rStartY + 1));

	// get ganglion cell's coordinates and amount of ganglion cells
	gXY = (int2)(get_global_id(0), get_global_id(1));
	gSizeXY = (int2)(get_global_size(0), get_global_size(1));

	// if left or right edge modify receptive field
	if (gXY.x == 1)
		rStartX = 0;
	else if (gXY.x == gSizeXY.x - 1)
		rEndX = 0;

	// if top or bottom edge modify receptice field
	if (gXY.y == 1)
		rStartY = 0;
	else if (gXY.y == gSizeXY.y - 1)
		rEndY = 0;

	// on-center / off-surround algorithm
	gBW = gBias;
//	gRG = gBias;
//	gYB = gBias;

	for (int dy = rStartY; dy <= rEndY; dy++)
	{
		for (int dx = rStartX; dx <= rEndX; dx++)
		{
			// get receptor cell's coordinates
			rXY = (int2)(gXY.x + dx, gXY.y + dy);

			// get receptor cell's input RBGA color
			rColor = read_imagef(Tex2D_input, sampler, rXY);

//			rLuminance = max(rColor.x, max(rColor.y, rColor.z));
			rLuminance = (rColor.x + rColor.y + rColor.z) / 3.0f;

			// if receptor cell on-center
			if (dx == 0 && dy == 0)
			{
				gBW += rLuminance * rCW;
			}
			// if receptor cell off-surround
			else
			{
				gBW += rLuminance * rSW;
			}	
		}
	}

	float R;
	float G;

	if (gBW > 0.535)
		R = 1.0;
	else if (gBW < 0.465)
		G = 1.0;
	else
	{
		R = 0.0;
		G = 0.0;
	}
	write_imagef(Tex2D_retinaBW, gXY, (float4)(R, G, 0.0f, 1.0f));
}
