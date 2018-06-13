#pragma once

template <typename T>
class Array2D
{
public:
	Array2D() = default;
	Array2D(const Array2D&) = delete;
	Array2D& operator=(const Array2D&) = delete;
	~Array2D()
	{
		delete[] mData;
		mData = nullptr;
	}

public:
	void SetSize(int width, int height)
	{
		mWidth = width;
		mHeight = height;

		mData = new T[width * height];
	}

	T& operator()(int x, int y)
	{
		return mData[y * mWidth + x];
	}

	const T& operator()(int x, int y) const
	{
		return mData[y * mWidth + x];
	}

private:
	T *mData = nullptr;
	int mWidth = 0;
	int mHeight = 0;
};