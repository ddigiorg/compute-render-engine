// ============
// particles.cl
// ============

__kernel void physics2D(
	__global float2* pos, 
	__global float2* vel, 
	__global int2* mousePos,
	__global int2* windowDims
) {
	unsigned int gid = get_global_id(0);

	float2 d;            // distanceXY
	float2 p = pos[gid]; // positionXY
	float2 v = vel[gid]; // velocityXY
	float2 a;            // accelerationXY

	float distance; 
	float force;

	// Distance from particle to mouse pointer
	d.x = mousePos[0].x - p.x;
	d.y = mousePos[0].y - p.y;
	distance = sqrt(d.x * d.x + d.y * d.y); 

	if (distance < 50.0)
		distance = 50.0;
	else if (distance > 200.0)
		distance = 200.0;

	// Force
	force = 1000.0 / (distance * distance);

	// Acceleration
	a.x = (d.x / distance) * force;
	a.y = (d.y / distance) * force;

	// Velocity
	v.x += a.x;
	v.y += a.y;

	// Position
	p.x += v.x;
	p.y += v.y;

	// Window Boundaries
	if (p.x < 0.0)
		p.x = windowDims[0].x;
	else if (p.x > windowDims[0].x)
		p.x = 0.0;

	if (p.y < 0.0)
		p.y = windowDims[0].y;
	else if (p.y > windowDims[0].y)
		p.y = 0.0;

	// Velocity Decay
	v.x *= 0.995;
	v.y *= 0.995;

	pos[gid] = p;
	vel[gid] = v;
}
