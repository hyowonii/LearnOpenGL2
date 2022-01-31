#include "shader.h"
#include <cmath>

using namespace raytraceData;

shader::shader()
{
}

shader::~shader()
{
}

material* shader::makeMaterial(GLfloat r, GLfloat g, GLfloat b, GLfloat amb) {
	material* m;

	/* allocate memory */
	m = new material();

	/* put stuff in it */
	m->c.r = r;
	m->c.g = g;
	m->c.b = b;
	m->amb = amb;
	return(m);
}

/* LIGHTING CALCULATIONS */
struct Light {
	float direction[3] = { 1.0f, 1.0f, 1.0f };
	float intensity[3] = { 1.0f, 1.0f, 1.0f };
	
};

/* shade */
/* color of point p with normal vector n and material m returned in c */
void shader::shade(point* p, vector* n, material* m, color* c) {
	Light light;

	float diffuse_ref[3] = { 1.0f, 1.0f, 1.0f };
	float light_specular[3] = { 0.1f, 0.1f, 0.1f };

	/* so far, just finds ambient component of color */
	float NL = n->x * light.direction[0] + n->y * light.direction[1] + n->z * light.direction[2];
	float diffuse = max(0.0, (diffuse_ref[0] * light.intensity[0] + diffuse_ref[1] * light.intensity[1] + diffuse_ref[2] * light.intensity[2]) * NL);
	
	float specular;
	float R[3];
	R[0] = 2 * NL * (n->x) - light.direction[0];
	R[1] = 2 * NL * (n->y) - light.direction[1];
	R[2] = 2 * NL * (n->z) - light.direction[2];
	float VR = (0.0f - (p->x)) * R[0] + (0.0f - (p->y)) * R[1] + (0.0f - (p->z)) * R[2];
	if (NL > 0 && VR > 0) {
		specular = (light_specular[0] * light.intensity[0] + light_specular[1] * light.intensity[1] + light_specular[2] * light.intensity[2]) * pow(VR, 32.0f);
	}
	else {
		specular = 0.0;
	}
	
	c->r = (m->amb + diffuse + specular) * m->c.r;	// + diffuse + specular
	c->g = (m->amb + diffuse + specular) * m->c.g;
	c->b = (m->amb + diffuse + specular) * m->c.b;

	/* clamp color values to 1.0 */
	if (c->r > 1.0) c->r = 1.0;
	if (c->g > 1.0) c->g = 1.0;
	if (c->b > 1.0) c->b = 1.0;

}