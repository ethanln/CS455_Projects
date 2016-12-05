using UnityEngine;
using System;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using System.Collections;

public class MisslePivotController : MonoBehaviour {

    public float gizmoSize = 60.75f;
    public Color gizmoColor = Color.yellow;

    public GameObject monster_boundary;

    public Text timer;
    private string timer_header;
    private string current_time;
    
    private float turnSpeed = 100.0f;
    public static float rocketSpeed = 2.0f;

    private float initial_hor_rotation;
    private float initial_ver_rotation;

    private bool isLaunched;

    public static Vector3 lastPlanePos;
    public static Vector3 currentPlaneVelocity;

    // Use this for initialization
    void Start () {
        this.isLaunched = false;
        this.initial_hor_rotation = this.transform.rotation.x;
        this.initial_ver_rotation = this.transform.rotation.y;


        this.timer_header = "Timer: ";
        this.current_time = "45:00";

        this.timer.text = this.timer_header + this.current_time;
        this.timer.fontSize = 20;

        MisslePivotController.lastPlanePos = this.transform.position;
    }
	
	// Update is called once per frame
	void Update () {

        if (this.isLaunched)
        {
            this.checkMonsterCollision();
            this.updateTimer();
            this.checkTimer();


            if (Input.GetKey(KeyCode.W))
            {
                MisslePivotController.rocketSpeed += 0.1f;
            }
            if (Input.GetKey(KeyCode.S))
            {
                MisslePivotController.rocketSpeed -= 0.1f;
            }
            if (Input.GetKey(KeyCode.A))
            {
                transform.Rotate(0.0f, 0.0f, (this.turnSpeed * Time.deltaTime));
            }
            if (Input.GetKey(KeyCode.D))
            {
                transform.Rotate(0.0f, 0.0f, -(this.turnSpeed * Time.deltaTime));
            }
            if (Input.GetAxis("Mouse Y") < 0)
            {
                transform.Rotate(Vector3.down, this.turnSpeed * Time.deltaTime);
            }
            if (Input.GetAxis("Mouse Y") > 0)
            {
                transform.Rotate(Vector3.down, -this.turnSpeed * Time.deltaTime);
            }
            if (Input.GetAxis("Mouse X") < 0)
            {
                transform.Rotate(Vector3.right, this.turnSpeed * Time.deltaTime);
            }
            if(Input.GetAxis("Mouse X") > 0)
            {
                transform.Rotate(Vector3.left, this.turnSpeed * Time.deltaTime);
            }

            transform.Translate(Vector3.forward * rocketSpeed * Time.deltaTime);
        }
        else if (Input.GetKey(KeyCode.Space) && !this.isLaunched)
        {
            this.isLaunched = true;
        }
    }

    void OnDrawGizmo()
    {
        Gizmos.color = this.gizmoColor;
        Gizmos.DrawWireSphere(transform.position, this.gizmoSize);
    }

    private void updateTimer()
    {
        float dTime = Time.deltaTime;
        float newTime = (float)Convert.ToDouble(this.current_time.Replace(':', '.')) - dTime;
        this.current_time = newTime.ToString("F").Replace('.', ':');
        this.timer.text = this.timer_header + this.current_time;

        if ((float)Convert.ToDouble(this.current_time.Replace(':', '.')) - dTime <= 5.0)
        {
            this.timer.color = Color.red;
        }
    }

    private void checkTimer()
    {
        if((float)Convert.ToDouble(this.current_time.Replace(':', '.')) <= 0.0f)
        {
            MisslePivotController.rocketSpeed = 2.0f;
            SceneManager.LoadScene(SceneManager.GetActiveScene().name);
        }
    }

    private void checkMonsterCollision()
    {
        SphereCollider collider = this.monster_boundary.GetComponent<SphereCollider>();
        if (collider.bounds.Contains(this.transform.position))
        {
            MisslePivotController.rocketSpeed = 2.0f;
            SceneManager.LoadScene(SceneManager.GetActiveScene().name);
        }
    }

    void OnTriggerEnter(Collider col)
    {

        if (col.gameObject.name == "bomb_prefab")
        {
            return;
        }
    }

    void OnTriggerExit(Collider col)
    {

        if (col.gameObject.name == "bomb_prefab")
        {
            return;
        }
    }
}
