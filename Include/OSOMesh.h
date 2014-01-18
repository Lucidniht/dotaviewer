#pragma once

#include <directxmath.h>
#include "OSOTypes.h"


namespace OSO
{
    class Mesh
    {
        
        public:
            struct SubMesh
            {
                unsigned int index_offset;
                int triangle_count;
                
                SubMesh() : index_offset(0), triangle_count(0) {}
            };
            
            enum
            {
                MAX_VERTEX_BUFFER_COUNT = 6
            };
            
            
        public: 
            Mesh();
            ~Mesh();
            
            
            void Initialize(IDirect3DDevice* _device, Entity* e, FbxNode* fbx_node);
            
            void Update();
            void Render(const D3DXMATRIX& world_matrix, const D3DXMATRIX& view_matrix, const D3DXMATRIX& projection_maxtrix);
            
            void RenderSubMesh();
            
            Material* GetMaterial(int i)
            {
                if (i < material_list.size())
                {
                    return material_list[i];
                }
                
                return NULL;
            };
            
            void SetDevice(IDirect3DDevice9* _device) { d3d_device = _device; }
            void SetEntity(Entity* e) { entity = e; }
            void SetVertexCount(int c) { vertex_count = c; }
            
            void SetVertexDeclaration(IDirect3DVertexDeclaration9* _de) { vertex_declare = _de; }
            void SetVertexBuffer(int i, IDirect3DVertexBuffe9* b)
            {
                if (i < MAX_VERTEX_BUFFER_COUNT)
                {   
                    vertex_buffers[i] = b;
                }
            }
            
            void SetVertexBufferCount(size_t c) { vertex_buffer_count = c; }
            void SetVertexBufferStride(int i, size_t c)
            {
                if( i < MAX_VERTEX_BUFFER_COUNT)
                {
                    buffer_strides[i] = c;
                }
            }
            
            void SetIndexBuffer(IDirect3DIndexBuffer9* b) { index_buffer = b; has_index_list = true; }
            
            std::vector<Material*>& GetMaterialList() { return material_list; }
            std::vector<SubMesh*>& GetSubMeshList() { return sub_mesh_list; }
            
        public:
            
            void InitVertexElement(D3DVERTEXELEMENT9& cur_element, WORD stream, WORD offset, BYTE type, BYTE method, BYTE usage, BYTE usage_index)
            {
                cur_element.Stream = sream;
                cur_element.Offset = offset;
                cur_element.Type = type;
                cur_element.Method = method;
                cur_element.Usage = usage;
                cur_element.UsageIndex = usage_index;
            }
        
        private:
            void LoadMaterials(FbxNode* fbx_node);
            
        private:
            Entity* entity;
            
            int vertex_count;
            
            bool has_uv;
            bool has_normal;
            bool has_tanget;
            bool has_index_list;
            
            std::vector<Material*> material_list;
            std::vector<SubMesh*> sub_mesh_list;
            std::vector<Skelton*> skelton_list;
            
            D3DXMATRIX* blend_matrix_list;
            int blend_matrix_count;
            
            IDirect3DIndexBuffer9* index_buffer;
            IDirect3DVertexBuffe9* vertex_buffers[NAX_VERTEX_BUFFER_COUNT];
            size_t buffer_strides[NAX_VERTEX_BUFFER_COUNT];
            size_t vertex_buffer_count;
            
            IDirect3DVertexDeclaration9* vertex_declare; // TODO 应该移动到Entity下， 每个Entity包含的顶点格式应该保持一致
            D3DXMATRIX offset_matrix;
            
    };
}
