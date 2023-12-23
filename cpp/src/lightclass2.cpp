#include "lightclass2.h"

LightClass2::LightClass2() {}
LightClass2::LightClass2(const LightClass2 &other) {}
LightClass2::~LightClass2() {}

void LightClass2::SetDiffuseColor(float red, float green, float blue,
                                  float alpha) {
  m_diffuseColor[0] = red;
  m_diffuseColor[1] = green;
  m_diffuseColor[2] = blue;
  m_diffuseColor[3] = alpha;
}

void LightClass2::SetDirection(float x, float y, float z) {
  m_direction[0] = x;
  m_direction[1] = y;
  m_direction[2] = z;
}

void LightClass2::SetAmbientLight(float red, float green, float blue,
                                  float alpha) {
  m_ambientLight[0] = red;
  m_ambientLight[1] = green;
  m_ambientLight[2] = blue;
  m_ambientLight[3] = alpha;
}
void LightClass2::SetSpecularColor(float red, float green, float blue,
                                   float alpha) {
  m_specularColor[0] = red;
  m_specularColor[1] = green;
  m_specularColor[2] = blue;
  m_specularColor[3] = alpha;
}
void LightClass2::SetSpecularPower(float power) { m_specularPower = power; }

void LightClass2::GetDiffuseColor(float *color) {
  color[0] = m_diffuseColor[0];
  color[1] = m_diffuseColor[1];
  color[2] = m_diffuseColor[2];
  color[3] = m_diffuseColor[3];
}

void LightClass2::GetDirection(float *direction) {
  direction[0] = m_direction[0];
  direction[1] = m_direction[1];
  direction[2] = m_direction[2];
}

void LightClass2::GetAmbientLight(float *ambient) {
  ambient[0] = m_ambientLight[0];
  ambient[1] = m_ambientLight[1];
  ambient[2] = m_ambientLight[2];
  ambient[3] = m_ambientLight[3];
}

void LightClass2::GetSpecularColor(float *specular) {
  specular[0] = m_specularColor[0];
  specular[1] = m_specularColor[1];
  specular[2] = m_specularColor[2];
  specular[3] = m_specularColor[3];
}

void LightClass2::GetSpecularPower(float &power) { power = m_specularPower; }
