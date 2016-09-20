#pragma once

using namespace std;

class camera 
{
	private:
		float orientation;
		float cam_x;
		float cam_y;
		float cam_z;

	public:

		camera(float _orientation, float _cam_x, float _cam_y, float _cam_z);

		~camera();

		float getOrientation();

		float getCamX();

		float getCamY();

		float getCamZ();

		void setCam(float _cam_x, float _cam_y, float _cam_z);

		void setCamX(float _cam_x);

		void setCamY(float _cam_y);

		void setCamZ(float _cam_z);

		void setOrientation(float _orientation);
};
