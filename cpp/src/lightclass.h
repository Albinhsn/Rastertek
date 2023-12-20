#ifndef LIGHTCLASS_H
#define LIGHTCLASS_H


class LightClass{
public:
  LightClass();
  LightClass(const LightClass&);
  ~LightClass();

  void SetDiffuseColor(float, float, float, float);
  void SetDirection(float, float, float);
  void SetAmbientLight(float, float, float, float);

  void GetDiffuseColor(float*);
  void GetDirection(float*);
  void GetAmbientLight(float*);

private:
  float m_diffuseColor[4];
  float m_direction[3];
  float m_ambientLight[4];
};

#endif
