#include "OSOCamera.h"

namespace OSO
{
    Camera::Camera()
    {

    }

    Camera::~Camera()
    {

    }

    void Camera::SetLens( float fovy, float _aspect, float zn, float zf)
    {
        near_clipping_z = zn;
        far_clipping_z = zf;
        field_of_view_y = fovy;
        aspect = _aspect;

        XMMATRIX m = DirectX::XMMatrixPerspectiveFovLH(field_of_view_y, aspect, near_clipping_z, far_clipping_z);
        DirectX::XMStoreFloat4x4(&projection_matrix, m);
    }

    void Camera::LookAt( const XMVECTOR& _pos, const XMVECTOR& _target, const XMVECTOR& _up )
    {
        XMVECTOR L = XMVector3Normalize(DirectX::XMVectorSubtract(_target, _pos));
	    XMVECTOR R = XMVector3Normalize(DirectX::XMVector3Cross(_up, L));
	    XMVECTOR U = XMVector3Cross(L, R);

        XMStoreFloat3(&position, _pos);
	    XMStoreFloat3(&look, L);
	    XMStoreFloat3(&right, R);
	    XMStoreFloat3(&up, U);
    }

    void Camera::Pitch( float angle )
    {
    	XMMATRIX R = DirectX::XMMatrixRotationAxis(XMLoadFloat3(&right), angle);

	    XMStoreFloat3(&up, XMVector3TransformNormal(XMLoadFloat3(&up), R));
	    XMStoreFloat3(&look, XMVector3TransformNormal(XMLoadFloat3(&look), R));
    }

    void Camera::Roll( float angle )
    {

    }

    void Camera::Yaw( float angle )
    {
        XMMATRIX R = DirectX::XMMatrixRotationY(angle);

	    XMStoreFloat3(&right, XMVector3TransformNormal(XMLoadFloat3(&right), R));
	    XMStoreFloat3(&up, XMVector3TransformNormal(XMLoadFloat3(&up), R));
	    XMStoreFloat3(&look, XMVector3TransformNormal(XMLoadFloat3(&look), R));
    }

    void Camera::Update()
    {
        XMVECTOR R = XMLoadFloat3(&right);
	    XMVECTOR U = XMLoadFloat3(&up);
	    XMVECTOR L = XMLoadFloat3(&look);
	    XMVECTOR P = XMLoadFloat3(&position);

	    // Keep camera's axes orthogonal to each other and of unit length.
	    L = DirectX::XMVector3Normalize(L);
	    U = XMVector3Normalize(XMVector3Cross(L, R));

	    // U, L already ortho-normal, so no need to normalize cross product.
	    R = XMVector3Cross(U, L); 

	    // Fill in the view matrix entries.
	    float x = -XMVectorGetX(XMVector3Dot(P, R));
	    float y = -XMVectorGetX(XMVector3Dot(P, U));
	    float z = -XMVectorGetX(XMVector3Dot(P, L));

	    XMStoreFloat3(&right, R);
	    XMStoreFloat3(&up, U);
	    XMStoreFloat3(&look, L);

	    view_matrix(0,0) = right.x; 
	    view_matrix(1,0) = right.y; 
	    view_matrix(2,0) = right.z; 
	    view_matrix(3,0) = x;   

	    view_matrix(0,1) = up.x;
	    view_matrix(1,1) = up.y;
	    view_matrix(2,1) = up.z;
	    view_matrix(3,1) = y;  

	    view_matrix(0,2) = look.x; 
	    view_matrix(1,2) = look.y; 
	    view_matrix(2,2) = look.z; 
	    view_matrix(3,2) = z;   

	    view_matrix(0,3) = 0.0f;
	    view_matrix(1,3) = 0.0f;
	    view_matrix(2,3) = 0.0f;
	    view_matrix(3,3) = 1.0f;

    }
}