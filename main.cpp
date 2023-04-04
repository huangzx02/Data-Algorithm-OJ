#include<stdio.h>
#pragma warning (disable:4996)

double fabs(const double& x)
{
	return x >= 0 ? x : -x;
}

class Vec
{
public:
	Vec():x(0),y(0),z(0){}
	Vec(double x,double y, double z):x(x),y(y),z(z){}
	~Vec(){}
	bool operator ==(const Vec& v)const
	{
		return (fabs(x - v.x) < 0.05) && (fabs(y - v.y) < 0.05) && (fabs(z - v.z) < 0.05);
	}
	Vec operator -(const Vec& v)const
	{
		return Vec(x - v.x, y - v.y, z - v.z);
	}
	Vec& operator =(const Vec& v)
	{
		if (this != &v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
		}
		return *this;
	}
	double x;
	double y;
	double z;
};

Vec buf[5];
int n, g = 0, cnt = 0;

Vec cross(const Vec& v1, const Vec& v2)
{
	return Vec(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

bool IsPar(const Vec& v1, const Vec& v2)
{
	return cross(v1, v2) == Vec(0, 0, 0);
}

Vec Getn(const Vec& v1, const Vec& v2, const Vec& v3)
{
	return cross(v1 - v2, v1 - v3);
}

bool IsLine(const Vec& v1, const Vec& v2, const Vec& v3)
{
	return Getn(v1, v2, v3) == Vec(0, 0, 0);
}

void input()
{
	for (int i = cnt; i < n; i++)
	{
		scanf("%lf%lf%lf", &buf[0].x, &buf[0].y, &buf[0].z);
	}
}

void search(const Vec& v)
{
	Vec cur;
	bool f = 1;
	int i = 0;
	for(i = cnt; i < n; i++)
	{
		scanf("%lf%lf%lf", &cur.x, &cur.y, &cur.z);
		if (f)
		{
			if (!IsPar(v, Getn(cur, buf[0], buf[1])))
			{
				g = i;
				f = 0;
			}
		}
	}
}

int main()
{
	int i = 0, j = 0, m = 0;
	int r[5];
	bool flag = 0;
	Vec n1, n2, n3;
	scanf("%d", &n);
	while (i < 5)
	{
		scanf("%lf%lf%lf", &buf[i].x, &buf[i].y, &buf[i].z);
		cnt++;
		if (cnt == n)//数据中没有互不三点共线的五个点
		{
			//处理数据
			break;
		}
		{

		}
		for (j = 0; j < i - 1; j++)
		{
			for (m = j + 1; m < i; m++)
			{
				if (IsLine(buf[i], buf[j], buf[m]))
				{
					flag = 1;//有共线情况，舍去
					break;
				}
			}
			if (flag)
			{
				break;
			}
		}
		if (flag)//有共线还原标志
		{
			flag = 0;
		}
		else
		{
			r[cnt - 1] = i;
			i++;
		}
	}
	n1 = Getn(buf[0], buf[1], buf[2]);
	n2 = Getn(buf[0], buf[1], buf[3]);
	n3 = Getn(buf[0], buf[1], buf[4]);
	if (IsPar(n1, n2))
	{
		if (IsPar(n1, n3))
		{
			search(n1);
		}
		else
		{
			g = r[4];
			input();
		}
	}
	else//n1&n2不平行
	{
		if (IsPar(n1, n3))
		{
			g = r[3];
		}
		else if (IsPar(n2, n3))
		{
			g = r[2];
		}
		else
		{
			Vec n4 = Getn(buf[2], buf[3], buf[4]), n5 = Getn(buf[1], buf[2], buf[3]);
			if (IsPar(n4, n5))
			{
				g = r[0];
			}
			else
			{
				g = r[1];
			}
		}
		input();
	}
	printf("%d\n", g);
	return 0;
} 