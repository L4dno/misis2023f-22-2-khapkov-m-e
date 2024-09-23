// part of the terrain
constexpr uint16_t SectorSize = 256;

class TerrainSector
{
public:
	// list of high values from highmap
	std::vector<float> heightmap;

	float textureSize = 64;

	uint16_t width = SectorSize;
	uint16_t height = SectorSize;

	// init container for the points
	void Setup()
	{
		heightmap.reserve(width * height);

		for (uint16_t v = 0; v < height; v++)
		{
			for (uint16_t h = 0; h < width; h++)
			{
				heightmap.push_back(0);
			}
		}
	}

	// get color depth from the image
	void SetupImage(Image& img)
	{
		ImageResize(&img, width, height);

		for (uint16_t v = 0; v < height; v++)
		{
			for (uint16_t h = 0; h < width; h++)
			{
				float param = GetImageColor(img, h, v).r / 255.0f;

				param *= 35; // scale;

				SetHeightmapValue(h, v, param);
			}
		}
	}

	// convert x and y to monoindex
	inline size_t GetIndex(uint16_t h, uint16_t v)
	{
		return (size_t(v) * width) + h;
	}

	//  check if pos on the terrain
	bool IsPosValid(uint16_t h, uint16_t v)
	{
		return (h >= 0 && h < width && v >= 0 && v < height);
	}


	float GetHeightmapValue(uint16_t h, uint16_t v)
	{
		if (heightmap.size() == 0)
			Setup();

		if (!IsPosValid(h, v))
			return 0;

		return heightmap[GetIndex(h, v)];
	}


	void SetHeightmapValue(uint16_t x, uint16_t y, float value)
	{
		if (heightmap.size() == 0)
			Setup();
		heightmap[GetIndex(x, y)] = value;
	}

	// method to set verts in triangles
	void BuildMesh(Mesh& mesh)
	{
		GeomtryBuilder builder(mesh);
		builder.Allocate(((width - 1) * (height - 1)) * 2);

		int triangleIndex = 0;
		int vertIndex = 0;

		for (uint16_t v = 0; v < height - 1; v++)
		{
			for (uint16_t h = 0; h < width - 1; h++)
			{
				auto setVert = [&builder, this](uint16_t _h, uint16_t _v)
					{
						builder.SetSetUV((_h / float(width)) * textureSize, (_v / float(height)) * textureSize);
						builder.SetSetUV2((_h / float(width)), (_v / float(height)));
						builder.PushVertex(Vector3{ float(_h),float(_v), GetHeightmapValue(_h,_v) });
					};

				setVert(h, v);
				setVert(h + 1, v);
				setVert(h + 1, v + 1);

				setVert(h, v);
				setVert(h + 1, v + 1);
				setVert(h, v + 1);

			}
		}
	}
};