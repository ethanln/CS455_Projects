#include "stdafx.h"
#include "GraphicObject.h"

using namespace std;

GraphicObject::GraphicObject(string _object_uri)
{
	// parse obj file.
	ObjectParser* parser = new ObjectParser();
	parser->parse(_object_uri, this->faces);
}

vector<face> GraphicObject::getObjectFaces()
{
	return this->faces;
}

bool GraphicObject::loadTexture(string _texture_uri) {
	printf("Reading image %s\n", _texture_uri);

	// Data read from the header of the BMP file
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int imageSize;
	unsigned int width, height, bpp;
	// Actual RGB data
	unsigned char * data;

	// Open the file
	FILE * file = fopen(_texture_uri.c_str(), "rb");
	if (!file)
	{
		printf("Image could not be opened\n");
		return false;
	}

	// Read the header, i.e. the 54 first bytes

	// If less than 54 byes are read, problem
	if (fread(header, 1, 54, file) != 54) {
		printf("Not a correct BMP file\n");
		return false;
	}

	// A BMP files always begins with "BM"
	if (header[0] != 'B' || header[1] != 'M') {
		printf("Not a correct BMP file\n");
		return 0;
	}
	// Make sure this is a 24bpp file
	if (*(int*)&(header[0x1E]) != 0) { printf("Not a correct BMP file\n");    return 0; }
	if (*(int*)&(header[0x1C]) != 24) { printf("Not a correct BMP file\n");    return 0; }

	// Read the information about the image
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);
	bpp = 3;

	// Some BMP files are misformatted, guess missing information
	if (imageSize == 0)
	{
		imageSize = width*height * 3; // 3 : one byte for each Red, Green and Blue component
	}

	if (dataPos == 0)
	{
		dataPos = 54;
	}

	// Create a buffer
	data = new unsigned char[imageSize];

	// Read the actual data from the file into the buffer
	fread(data, 1, imageSize, file);

	// Everything is in memory now, the file wan be closed
	fclose(file);

	// Swap Red and Blue component for each texel of the image
	unsigned char t;
	for (unsigned int i = 0; i < imageSize; i += 3)
	{
		t = data[i];
		data[i] = data[i + 2];
		data[i + 2] = t;
	}

	if (data == NULL) {
		std::cout << "Texture failed to load";
	}
	// Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	// ... nice trilinear filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Return the ID of the texture we just created
	this->texId = textureID;

	return true;
}

void GraphicObject::display()
{
	/* TEXTURES SETUP */
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, this->texId);
	//glDepthFunc(GL_EQUAL);

	for (unsigned int i = 0; i < this->faces.size(); i++)
	{
		glBegin(GL_POLYGON);
			vector<material> faceMaterial = this->faces.at(i).getFaceMaterial();
			for (unsigned int j = 0; j < faceMaterial.size(); j++)
			{
				glm::vec4 vec(faceMaterial.at(j).vertex.x, faceMaterial.at(j).vertex.y, faceMaterial.at(j).vertex.z, 1.0f);
				glm::vec4 transformed_vec = graphics_pipeline::transform(vec);
				glm::vec3 screen_vec = graphics_pipeline::to_screen(transformed_vec);

				glTexCoord2f(faceMaterial.at(j).uv.x, faceMaterial.at(j).uv.y);
				//glVertex3f(faceMaterial.at(j).vertex.x, faceMaterial.at(j).vertex.y, faceMaterial.at(j).vertex.z);
				//glNormal3f(faceMaterial.at(j).normal.x, faceMaterial.at(j).normal.y, faceMaterial.at(j).normal.z);
				glVertex2f(screen_vec.x, screen_vec.y);
			}
		glEnd();
	}

	glFlush();

	glDisable(GL_TEXTURE_2D);
}

GraphicObject::~GraphicObject()
{
}