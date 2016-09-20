#include "stdafx.h"
#include "ObjectParser.h"

using namespace std;

bool ObjectParser::parse(string file_path,
	vector<glm::vec3> &out_vertices,
	vector<glm::vec2> &out_uvs,
	vector<glm::vec3> &out_normals)
{
	string new_file_path = "..\\..\\src\\" + file_path;
	FILE * file = fopen(file_path.c_str(), "r");

	if (file == NULL)
	{
		printf("File doesn't exists \n");
		return false;
	}
	else
	{
		printf("File does exist \n");
	}

	while (1)
	{
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
		{
			break; // EOF = End Of File. Quit the loop.
		}

		if (strcmp(lineHeader, "v") == 0)
		{
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0)
		{
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0)
		{
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0)
		{
			std::string vertex1;
			std::string vertex2;
			std::string vertex3;

			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9)
			{
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}

	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		out_vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < uvIndices.size(); i++)
	{
		unsigned int uvIndex = uvIndices[i];
		glm::vec2 uv = temp_uvs[uvIndex - 1];
		out_uvs.push_back(uv);
	}

	for (unsigned int i = 0; i < normalIndices.size(); i++)
	{
		unsigned int normalIndex = normalIndices[i];
		glm::vec3 normal = temp_normals[normalIndex - 1];
		out_normals.push_back(normal);
	}

	return true;
}

bool ObjectParser::parse(string file_path, vector<face> &faces) 
{
	FILE *objfile = fopen(file_path.c_str(), "r");
	if (objfile == NULL)
	{
		std::cout << "Error loading file " << file_path << std::endl;
		return false;
	}
	char line[128];
	while (fgets(line, sizeof(line), objfile))
	{
		std::stringstream ss;
		ss << line;
		std::string tok;
		ss >> tok;
		if (tok == "v")
		{
			std::string sx, sy, sz;
			ss >> sx >> sy >> sz;
			double px = atof(sx.c_str());
			double py = atof(sy.c_str());
			double pz = atof(sz.c_str());
			//if (px > xmax) xmax = px;
			//if (py > ymax) ymax = py;
			//if (pz > zmax) zmax = pz;
			//if (px < xmin) xmin = px;
			//if (py < ymin) ymin = py;
			//if (pz < zmin) zmin = pz;

			glm::vec3 v(px, py, pz);
			temp_vertices.push_back(v);
		}
		else if (tok == "vt")
		{
			std::string sx, sy;
			ss >> sx >> sy;
			glm::vec2 v(atof(sx.c_str()), atof(sy.c_str()));
			temp_uvs.push_back(v);
		}
		else if (tok == "vn")
		{
			std::string nx, ny, nz;
			ss >> nx >> ny >> nz;
			glm::vec3 v(atof(nx.c_str()), atof(ny.c_str()), atof(nz.c_str()));
			temp_normals.push_back(v);
		}
		else if (tok == "f")
		{
			face f;
			//std::vector<int> face_pts;
			//std::vector<int> face_txs;
			//std::vector<int> face_nms;
			std::string face_str;
			ss >> face_str;
			while (!ss.eof())
			{
				int pt, vt, nm;
				sscanf(face_str.c_str(), "%d/%d/%d", &pt, &vt, &nm);
				f.addFaceMaterial(temp_vertices.at(pt - 1), temp_uvs.at(vt - 1), temp_normals.at(nm - 1));
				//face_pts.push_back(pt - 1);
				//face_txs.push_back(vt - 1);
				//face_nms.push_back(nm - 1);

				ss >> face_str;
			}
			//face f(face_pts, face_txs, face_nms);
			faces.push_back(f);
		}
	}

	fclose(objfile);
	return true;
}

void ObjectParser::print_info(std::ostream &out)
{
	out << "mesh" << std::endl;
	out << "  vertices: " << temp_vertices.size() << std::endl;
	out << "  faces: " << uvIndices.size() << std::endl;
}

