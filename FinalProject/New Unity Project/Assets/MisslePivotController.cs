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
    private float camera_toggle_delay;

    private float pause_delay;
    private bool timeout;

    public static Vector3 lastPlayerPos;
    public static Vector3 currentPlayerPos;
    public static bool isGameOver = false;
    public static bool isLoss = false;
    public static bool isVictory = false;
    public static bool isPause = false;

    // cameras:
    public Camera main_cam;
    public Camera bomb_cam;
    public Camera side_cam;

    // Use this for initialization
    void Start () {
        this.isLaunched = false;
        this.camera_toggle_delay = 0.0f;

        this.initial_hor_rotation = this.transform.rotation.x;
        this.initial_ver_rotation = this.transform.rotation.y;

        this.timer_header = "Timer: ";
        this.current_time = "45:00";

        this.timer.text = this.timer_header + this.current_time;

        MisslePivotController.lastPlayerPos = this.transform.position;
        MisslePivotController.currentPlayerPos = this.transform.position;

        this.main_cam.enabled = true;
        this.bomb_cam.enabled = false;
        this.side_cam.enabled = false;

        this.timeout = false;
    }
	
	// Update is called once per frame
	void Update () {
        if (MisslePivotController.isGameOver)
        {
            return;
        }

        this.pause_delay += .08f;

        if (Input.GetKey(KeyCode.Tab) 
            && MisslePivotController.isPause
            && this.pause_delay >= 1.0f)
        {
            MisslePivotController.isPause = false;
            Time.timeScale = 1.0f;
            this.pause_delay = 0.0f;
        }
        else if(Input.GetKey(KeyCode.Tab) 
            && !MisslePivotController.isPause
            && this.pause_delay >= 1.0f)
        {
            MisslePivotController.isPause = true;
            Time.timeScale = 0.0f;
            this.pause_delay = 0.0f;
        }

        if (MisslePivotController.isPause)
        {
            return;
        }

        if (this.isLaunched)
        {
            this.checkMonsterCollision();
            this.updateTimer();
            this.checkTimer();

            this.camera_toggle_delay += Time.deltaTime;

            if (Input.GetKey(KeyCode.Q) && this.camera_toggle_delay >= 0.2f)
            {
                this.camera_toggle_delay = 0.0f;
                this.bomb_cam.enabled = true;
                this.main_cam.enabled = false;
                this.side_cam.enabled = false;
            }
            if (Input.GetKey(KeyCode.E) && this.camera_toggle_delay >= 0.2f)
            {
                this.camera_toggle_delay = 0.0f;
                this.bomb_cam.enabled = false;
                this.main_cam.enabled = false;
                this.side_cam.enabled = true;
            }
            if (Input.GetKey(KeyCode.R) && this.camera_toggle_delay >= 0.2f)
            {
                this.camera_toggle_delay = 0.0f;
                this.bomb_cam.enabled = false;
                this.main_cam.enabled = true;
                this.side_cam.enabled = false;
            }
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

        // update plane position
        MisslePivotController.lastPlayerPos = currentPlayerPos;
        MisslePivotController.currentPlayerPos = this.transform.position;
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
        if((float)Convert.ToDouble(this.current_time.Replace(':', '.')) <= 0.0f
            && !MisslePivotController.isGameOver
            && !this.timeout)
        {
            MisslePivotController.isGameOver = true;
            MisslePivotController.isLoss = true;
            this.timeout = true;
        }
    }

    private void checkMonsterCollision()
    {
        CapsuleCollider collider = this.monster_boundary.GetComponent<CapsuleCollider>();
        if (collider.bounds.Contains(this.transform.position)
            && !MisslePivotController.isGameOver
            && !this.timeout)
        {
            MisslePivotController.isGameOver = true;
            MisslePivotController.isLoss = true;
            this.timeout = true;
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
