#include "modellistclass.h"

ModelListClass::ModelListClass() {}
ModelListClass::ModelListClass(const ModelListClass &other) {}
ModelListClass::~ModelListClass() {}

void ModelListClass::Initialize(int numModels) {
  int i;
  m_modelCount = numModels;

  m_ModelInfoList = new ModelInfoType[m_modelCount];

  srand((unsigned int)time(NULL));

  for (i = 0; i < m_modelCount; i++) {
    m_ModelInfoList[i].positionX =
        (((float)rand() - (float)rand()) / RAND_MAX) * 10.0f;
    m_ModelInfoList[i].positionY =
        (((float)rand() - (float)rand()) / RAND_MAX) * 10.0f;
    m_ModelInfoList[i].positionZ =
        (((float)rand() - (float)rand()) / RAND_MAX) * 10.0f + 5.0f;
  }
}

void ModelListClass::Shutdown(){
  if(m_ModelInfoList){
    delete [] m_ModelInfoList;
    m_ModelInfoList = 0;
  }
}

int ModelListClass::GetModelCount(){
  return m_modelCount;
}

void ModelListClass::GetData(int index, float & positionX, float & positionY, float & positionZ){
  positionX = m_ModelInfoList[index].positionX;
  positionY = m_ModelInfoList[index].positionY;
  positionZ = m_ModelInfoList[index].positionZ;
}
