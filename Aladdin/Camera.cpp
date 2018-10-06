#include "Camera.h"


Camera::Camera(int width, int height, float angle, D3DXVECTOR3 scaleFactors)
{
	this->m_Width = width;
	this->m_Height = height;
	this->m_Angle = angle;
	this->m_ScaleFactors = scaleFactors;

	D3DXMatrixOrthoLH(&m_OrthographicMatrix, (float)m_Width, -(float)m_Height, 0.0f, 1.0f);
	D3DXMatrixIdentity(&m_IdentityMatrix);

	isFollow = false;
}

Camera::Camera(void)
{
}

Camera::~Camera(void)
{
}

void Camera::Follow(Sprite *player)
{
	if (!isFollow)
	{
		isFollow = true;
		this->m_Sprite = player;
	}
}

void Camera::SetX(int x)
{
	this->m_Position.x = (float)x;
}

void Camera::Update()
{
	m_Position.x = this->m_Width / 2.0f / m_ScaleFactors.x;
	m_Position.y = this->m_Height / 2.0f / m_ScaleFactors.y;
	if (isFollow && this->m_Sprite != NULL)
	{
		m_Position.x = m_Sprite->GetPosition().x;
		m_Position.y = m_Sprite->GetPosition().y;

		if (m_Position.x < this->m_Width / 2.0f / m_ScaleFactors.x)
			m_Position.x = this->m_Width / 2.0f / m_ScaleFactors.x;
		if (m_Position.y < this->m_Height / 2.0f / m_ScaleFactors.y)
			m_Position.y = this->m_Height / 2.0f / m_ScaleFactors.y;
	}
	//MessageBox(NULL, std::to_string(m_Position.y).c_str(), "fds", MB_OK);
	m_ViewMatrix = D3DXMATRIX(
		m_ScaleFactors.x * cos(m_Angle), m_ScaleFactors.x * sin(m_Angle), 0, 0,
		-m_ScaleFactors.y * sin(m_Angle), m_ScaleFactors.y * cos(m_Angle), 0, 0,
		0, 0, m_ScaleFactors.z, 0,
		-m_Position.x * m_ScaleFactors.x * cos(m_Angle) + m_Position.y * m_ScaleFactors.y * sin(m_Angle), -m_Position.x * m_ScaleFactors.y * sin(m_Angle) - m_Position.y * m_ScaleFactors.y * cos(m_Angle), 0, 1
	);
}

void Camera::Update(ViewPort* viewPort)
{
	m_Position.x = (FLOAT)viewPort->GetX() + viewPort->GetWidth() / 2.0f;
	m_Position.y = (FLOAT)viewPort->GetY() + viewPort->GetHeight() / 2.0f;
	
	m_ViewMatrix = D3DXMATRIX(
		m_ScaleFactors.x * cos(m_Angle), m_ScaleFactors.x * sin(m_Angle), 0, 0,
		-m_ScaleFactors.y * sin(m_Angle), m_ScaleFactors.y * cos(m_Angle), 0, 0,
		0, 0, m_ScaleFactors.z, 0,
		-m_Position.x * m_ScaleFactors.x * cos(m_Angle) + m_Position.y * m_ScaleFactors.y * sin(m_Angle), -m_Position.x * m_ScaleFactors.y * sin(m_Angle) - m_Position.y * m_ScaleFactors.y * cos(m_Angle), 0, 1
	);
}

void Camera::UnFollow()
{
	m_Sprite = nullptr;
	isFollow = false;
}

bool Camera::IsFollowing()
{
	return isFollow;
}

void Camera::SetTransform(LPDIRECT3DDEVICE9 d3ddev) const
{
	d3ddev->SetTransform(D3DTS_PROJECTION, &m_OrthographicMatrix);
	d3ddev->SetTransform(D3DTS_WORLD, &m_IdentityMatrix);
	d3ddev->SetTransform(D3DTS_VIEW, &m_ViewMatrix);
}
