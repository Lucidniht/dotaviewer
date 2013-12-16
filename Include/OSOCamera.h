#include "OSOTypes.h"
#include <d3d11.h>

namespace OSO
{
    class Camera
    {
    public:
        Camera();
        ~Camera();

    public:
        const XMFLOAT3& GetPosition() const { return position; } 
        void SetPosition( const XMFLOAT3& vec) { position = vec; }

        void SetLens( float field_of_view_y, float aspect, float zn, float zf);
        void LookAt( const XMVECTOR& target, const XMVECTOR& up, const XMVECTOR& at );

        void Pitch( float angle );
        void Roll( float angle );
        void Yaw( float angle );

        void Update();
    public:
        const XMMATRIX& GetViewMatrix() const { return XMLoadFloat4x4(&view_matrix); }
        const XMMATRIX& GetProjectionMatrix() const { return XMLoadFloat4x4(&projection_matrix); }
        const XMMATRIX& GetViewProjectionMatrix() const { return GetViewMatrix() * GetProjectionMatrix(); }

    private:
        XMFLOAT3 position;

        XMFLOAT3 up;
        XMFLOAT3 look;
        XMFLOAT3 right;

        float near_clipping_z;
        float far_clipping_z;
        float aspect;
        float field_of_view_y;
        float height;
        float width;

        XMFLOAT4X4 view_matrix;
        XMFLOAT4X4 projection_matrix;

    };
}