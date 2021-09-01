#pragma once
#include "Renderer/Renderer.h"
#include <vector>

 class VertexBuffer
 {
 public:
 	VertexBuffer(const void* data, unsigned int size);
    template<typename type> void InsertStride(int count);

    void Bind();
 
 private:
     unsigned int vbID = 0;
     unsigned int vaID = 0;
     const void* data = nullptr;
     unsigned int size = 0;
     void AttributesBind();
     size_t GetStrideSize();
     std::vector<Type> strides;
 };

 template<typename type>
 void VertexBuffer::InsertStride(int count)
 {
	 Type strideDetails = Renderer::ConvertTypeToGLType<type>();
	 strideDetails.count = count;
	 strides.emplace_back(strideDetails);

 }
