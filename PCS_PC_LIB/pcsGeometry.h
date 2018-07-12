#ifndef PCSGEOMETRY_H
#define PCSGEOMETRY_H

#include <math.h>

typedef float PointCoordinateType; //������������
typedef float ScalarType; //��������

template <class Type> class Tuple3Tpl
{
public:
	//������Ԫ��Ԫ��
	union
	{
		struct
		{
			Type x, y, z;
		};
		Type u[3];
	};

	//! Default constructor
	/** Inits tuple to (0,0,0).
	**/
	inline Tuple3Tpl() : x(0), y(0), z(0) {}

	//! Constructor from a triplet of values
	/** Inits typle to (a,b,c).
	**/
	inline Tuple3Tpl(Type a, Type b, Type c) : x(a), y(b), z(c) {}

	//! Constructor from an array of 3 elements
	inline Tuple3Tpl(const Type p[]) : x(p[0]), y(p[1]), z(p[2]) {}

	//! Copy constructor
	inline Tuple3Tpl(const Tuple3Tpl& v) : x(v.x), y(v.y), z(v.z) {}
};

//3Dʸ����ģ��
template <class Type> class Vector3Tpl : public Tuple3Tpl<Type>
{
public:
	//Don't ask me what other x, y, z or u members this class could
	//use but it seems necessary for compilation on some platforms...
	using Tuple3Tpl<Type>::x;
	using Tuple3Tpl<Type>::y;
	using Tuple3Tpl<Type>::z;
	using Tuple3Tpl<Type>::u;

	//��ʼʸ�����캯��
	inline Vector3Tpl() : Tuple3Tpl<Type>() {}
	//���깹�캯��
	inline Vector3Tpl(Type x_, Type y_, Type z_) : Tuple3Tpl<Type>(x_, y_, z_) {}
	//����Ԫ������Ĺ��캯��
	inline Vector3Tpl(const Type p[]) : Tuple3Tpl<Type>(p) {}
	//���ƹ��캯��
	inline Vector3Tpl(const Vector3Tpl& v) : Tuple3Tpl<Type>(v) {}
	//int����Ĺ��캯�� 
	static inline Vector3Tpl Array(const int a[3]) { return Vector3Tpl(static_cast<Type>(a[0]), static_cast<Type>(a[1]), static_cast<Type>(a[2])); }
	//float����Ĺ��캯��
	static inline Vector3Tpl Array(const float a[3]) { return Vector3Tpl(static_cast<Type>(a[0]), static_cast<Type>(a[1]), static_cast<Type>(a[2])); }
	//double����Ĺ��캯��
	static inline Vector3Tpl Array(const double a[3]) { return Vector3Tpl(static_cast<Type>(a[0]), static_cast<Type>(a[1]), static_cast<Type>(a[2])); }
	//���
	inline Type dot(const Vector3Tpl& v) const { return (x*v.x) + (y*v.y) + (z*v.z); }
	//X��
	inline Vector3Tpl cross(const Vector3Tpl &v) const { return Vector3Tpl((y*v.z) - (z*v.y), (z*v.x) - (x*v.z), (x*v.y) - (y*v.x)); }
	//ƽ��
	inline Type norm2() const { return (x*x) + (y*y) + (z*z); }
	//����ƽ��������ǿ��˫��������� ������:��������Ԫ�ؾ���ֵ�е����ֵ��
	inline double norm2d() const { return static_cast<double>(x)*static_cast<double>(x)+static_cast<double>(y)*static_cast<double>(y)+static_cast<double>(z)*static_cast<double>(z); }
	inline Type norm() const { return sqrt(norm2()); }
	//����������ǿ��˫���������
	inline double normd() const { return sqrt(norm2d()); }
	//ͳһ����������
	inline void normalize()
	{
		Type n = norm2();
		if (n>0)
			*this /= sqrt(n);
	}
	//��һ������
	inline Vector3Tpl orthogonal() const
	{
		Vector3Tpl ort;
		vorthogonal(u, ort.u);
		return ort;
	}
	//������
	inline Vector3Tpl operator - () const
	{
		Vector3Tpl V(-x, -y, -z);
		return V;
	}
	//�ӷ�����
	inline Vector3Tpl& operator += (const Vector3Tpl& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}
	//���������
	inline Vector3Tpl& operator -= (const Vector3Tpl& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}
	//�˷�������������� 
	inline Vector3Tpl& operator *= (Type v)
	{
		x *= v;
		y *= v;
		z *= v;
		return *this;
	}
	//�����������������
	inline Vector3Tpl& operator /= (Type v)
	{
		x /= v;
		y /= v;
		z /= v;
		return *this;
	}
	//�ӷ����ӣ����ȼ��ߣ�
	inline Vector3Tpl operator + (const Vector3Tpl& v) const
	{
		return Vector3Tpl(x + v.x, y + v.y, z + v.z);
	}
	//��
	inline Vector3Tpl operator - (const Vector3Tpl& v) const
	{
		return Vector3Tpl(x - v.x, y - v.y, z - v.z);
	}
	//��
	inline Vector3Tpl operator * (Type s) const
	{
		return Vector3Tpl(x*s, y*s, z*s);
	}
	//��
	inline Vector3Tpl operator / (Type s) const
	{
		return Vector3Tpl(x / s, y / s, z / s);
	}
	//X��
	inline Vector3Tpl operator * (const Vector3Tpl& v) const
	{
		return cross(v);
	}
	//����
	inline Vector3Tpl& operator = (const Vector3Tpl &v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}
	//��
	inline Type operator && (const Vector3Tpl &v) const
	{
		return dot(v);
	}
	//ֱ��Э������ 
	inline Type& operator [] (unsigned i)
	{
		return u[i];
	}
	//ֱ��������ʣ������� 
	inline const Type& operator [] (unsigned i) const
	{
		return u[i];
	}

	static inline void vdivide(const Type p[], Type s, Type r[])
	{
		r[0] = p[0] / s;
		r[1] = p[1] / s;
		r[2] = p[2] / s;
	}
	static inline void vdivide(Type p[], Type s)
	{
		p[0] /= s;
		p[1] /= s;
		p[2] /= s;
	}
	static inline void vmultiply(const Type p[], Type s, Type r[])
	{
		r[0] = p[0] * s;
		r[1] = p[1] * s;
		r[2] = p[2] * s;
	}
	static inline void vmultiply(Type p[], Type s)
	{
		p[0] *= s;
		p[1] *= s;
		p[2] *= s;
	}
	static inline Type vdot(const Type p[], const Type q[])
	{
		return (p[0] * q[0]) + (p[1] * q[1]) + (p[2] * q[2]);
	}
	static inline void vcross(const Type p[], const Type q[], Type r[])
	{
		r[0] = (p[1] * q[2]) - (p[2] * q[1]);
		r[1] = (p[2] * q[0]) - (p[0] * q[2]);
		r[2] = (p[0] * q[1]) - (p[1] * q[0]);
	}
	static inline void vcopy(const Type p[], Type q[])
	{
		q[0] = p[0];
		q[1] = p[1];
		q[2] = p[2];
	}
	static inline void vset(Type p[], Type s)
	{
		p[0] = p[1] = p[2] = s;
	}
	static inline void vset(Type p[], Type x, Type y, Type z)
	{
		p[0] = x;
		p[1] = y;
		p[2] = z;
	}
	static inline void vadd(const Type p[], const Type q[], Type r[])
	{
		r[0] = p[0] + q[0];
		r[1] = p[1] + q[1];
		r[2] = p[2] + q[2];
	}
	static inline void vsubstract(const Type p[], const Type q[], Type r[])
	{
		r[0] = p[0] - q[0];
		r[1] = p[1] - q[1];
		r[2] = p[2] - q[2];
	}
	static inline void vcombination(Type a, const Type p[], Type b, const Type q[], Type r[])
	{
		r[0] = (a*p[0]) + (b*q[0]);
		r[1] = (a*p[1]) + (b*q[1]);
		r[2] = (a*p[2]) + (b*q[2]);
	}
	static inline void vcombination(const Type p[], Type b, const Type q[], Type r[])
	{
		r[0] = p[0] + (b*q[0]);
		r[1] = p[1] + (b*q[1]);
		r[2] = p[2] + (b*q[2]);
	}
	static inline void vnormalize(Type p[])
	{
		Type n = vnorm2(p);
		if (n>0)
			vdivide(p, sqrt(n));
	}
	static inline Type vnorm2(const Type p[])
	{
		return (p[0] * p[0]) + (p[1] * p[1]) + (p[2] * p[2]);
	}
	static inline Type vdistance2(const Type p[], const Type q[])
	{
		return ((p[0] - q[0])*(p[0] - q[0])) + ((p[1] - q[1])*(p[1] - q[1])) + ((p[2] - q[2])*(p[2] - q[2]));
	}
	static inline Type vnorm(const Type p[])
	{
		return sqrt(vnorm2(p));
	}
	static inline Type vdistance(const Type p[], const Type q[])
	{
		return sqrt(vdistance2(p, q));
	}
	//����
	static inline void vorthogonal(const Type p[], Type q[])
	{
		if (fabs(p[0]) <= fabs(p[1]) && fabs(p[0]) <= fabs(p[2]))
		{
			q[0] = 0; q[1] = p[2]; q[2] = -p[1];
		}
		else if (fabs(p[1]) <= fabs(p[0]) && fabs(p[1]) <= fabs(p[2]))
		{
			q[0] = -p[2]; q[1] = 0; q[2] = p[0];
		}
		else
		{
			q[0] = p[1]; q[1] = -p[0]; q[2] = 0;
		}
		vnormalize(q);
	}

};

//�������Ӷ���ά�����ĳ˷�  
inline Vector3Tpl<float> operator * (float s, const Vector3Tpl<float> &v)
{
	return v*s;
}
inline Vector3Tpl<double> operator * (double s, const Vector3Tpl<double> &v)
{
	return v*s;
}

//2Dʸ����ģ��
template <class Type> class Vector2Tpl
{
public:
	union
	{
		struct
		{
			Type x, y;
		};
		Type u[2];
	};

	inline Vector2Tpl(Type s = 0) : x(s), y(s) {}
	inline Vector2Tpl(Type x_, Type y_) : x(x_), y(y_) {}
	inline Vector2Tpl(const Vector2Tpl& v) : x(v.x), y(v.y) {}
	inline Type norm2() const
	{
		return (x*x) + (y*y);
	}
	inline Type norm() const
	{
		return sqrt(norm2());
	}
	inline void normalize()
	{
		Type n = norm2();
		if (n>0)
			*this /= sqrt(n);
	}
	inline Type dot(const Vector2Tpl& v) const
	{
		return (x*v.x) + (y*v.y);
	}
	inline Vector2Tpl& operator - ()
	{
		x = -x;
		y = -y;
		return *this;
	}
	inline Vector2Tpl& operator += (const Vector2Tpl& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}
	inline Vector2Tpl& operator -= (const Vector2Tpl& v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}
	inline Vector2Tpl& operator *= (Type v)
	{
		x *= v;
		y *= v;
		return *this;
	}
	inline Vector2Tpl& operator /= (Type v)
	{
		x /= v;
		y /= v;
		return *this;
	}
	inline Vector2Tpl operator + (const Vector2Tpl& v) const
	{
		return Vector2Tpl(x + v.x, y + v.y);
	}
	inline Vector2Tpl operator - (const Vector2Tpl& v) const
	{
		return Vector2Tpl(x - v.x, y - v.y);
	}
	inline Vector2Tpl operator * (Type s) const
	{
		return Vector2Tpl(x*s, y*s);
	}
	inline Vector2Tpl operator / (Type s) const
	{
		return Vector2Tpl(x / s, y / s);
	}
	inline Vector2Tpl& operator = (const Vector2Tpl &v)
	{
		x = v.x;
		y = v.y;
		return *this;
	}
	inline Type& operator [] (unsigned i)
	{
		return u[i];
	}
	inline const Type& operator [] (unsigned i) const
	{
		return u[i];
	}
};


//Ĭ��3Dʸ��
typedef Vector3Tpl<PointCoordinateType> pcsVector3d;

//doule 3Dʸ��
typedef Vector3Tpl<double> pcsVector3D;

//Ĭ��2Dʸ��
typedef Vector2Tpl<PointCoordinateType> pcsVector2d;

//int 2Dʸ��
typedef Vector2Tpl<int> pcsVector2D;

#endif // PCSGEOMETRY_H
