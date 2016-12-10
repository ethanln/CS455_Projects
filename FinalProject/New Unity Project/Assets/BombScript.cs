using UnityEngine;
using System.Collections;

public class BombScript : MonoBehaviour {

    private float bomb_speed;

    // Use this for initialization
    void Start ()
    {
        this.bomb_speed = MisslePivotController.rocketSpeed;
        this.transform.parent = null;
        Rigidbody rb = this.gameObject.GetComponent<Rigidbody>();

        float dx = MisslePivotController.currentPlayerPos.x - MisslePivotController.lastPlayerPos.x;
        float dy = MisslePivotController.currentPlayerPos.y - MisslePivotController.lastPlayerPos.y;
        float dz = MisslePivotController.currentPlayerPos.z - MisslePivotController.lastPlayerPos.z;

        float dxspeed = dx / Time.deltaTime;
        float dyspeed = dy / Time.deltaTime;
        float dzspeed = dz / Time.deltaTime;

        //rb.velocity = new Vector3(bomb_speed, dy, bomb_speed);
        if(this.bomb_speed < 0.0f)
        {
            rb.AddForce(Vector3.back * bomb_speed * 15.0f, ForceMode.Impulse);
        }
        else
        {
            rb.AddForce(Vector3.forward * bomb_speed, ForceMode.Impulse);
        }
        
    }
	
	// Update is called once per frame
	void Update () {
        //float dx = MisslePivotController.currentPlayerPos.x - MisslePivotController.lastPlayerPos.x;
        //float dy = MisslePivotController.currentPlayerPos.y - MisslePivotController.lastPlayerPos.y;
        //float dz = MisslePivotController.currentPlayerPos.z - MisslePivotController.lastPlayerPos.z;

        //float dspeed = Mathf.Sqrt(Mathf.Pow(dx, 2.0f) + Mathf.Pow(dz, 2.0f)) / Time.deltaTime;
        //if(bomb_speed < 0)
        //{
        //    dspeed = -1.0f * dspeed;
        //}
        //Vector3 dir = new Vector3(dx, dy, dz);
        //float dspeed = Mathf.Abs(1.0f - (dir.y / (dir.x + dir.y + dir.z))) * this.bomb_speed;

        //transform.Translate(Vector3.forward * (dspeed) * Time.deltaTime);
        //transform.Translate(Vector3.forward * (bomb_speed) * Time.deltaTime);
    }
}
