#pragma once

using namespace std;

class camera 
{
	private:
		float orientation_x;
		float orientation_y;
		float orientation_z;

		float cam_x;
		float cam_y;
		float cam_z;

	public:

		camera(float _orientation_x, float _orientation_y, float _orientation_z, float _cam_x, float _cam_y, float _cam_z);

		~camera();

		float getCamX();

		float getCamY();

		float getCamZ();

		void setCam(float _cam_x, float _cam_y, float _cam_z);

		void setCamX(float _cam_x);

		void setCamY(float _cam_y);

		void setCamZ(float _cam_z);

		float getOrientationX();

		float getOrientationY();

		float getOrientationZ();

		void setOrientation(float _orientation_x, float _orientation_y, float _orientation_z);

		void setOrientationX(float _orientation_x);

		void setOrientationY(float _orientation_y);

		void setOrientationZ(float _orientation_z);
		
};
