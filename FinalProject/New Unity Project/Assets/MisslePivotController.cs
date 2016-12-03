﻿using UnityEngine;
using System;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using System.Collections;

public class MisslePivotController : MonoBehaviour {

    public float gizmoSize = 60.75f;
    public Color gizmoColor = Color.yellow;

    public GameObject monster_boundary;
    public GameObject terrain_boundaries;

    public Text timer;

    private float moveSpeed = 10f;
    private float turnSpeed = 100f;
    private float rocketSpeed = 700f;

    private float pre_launch_rotate_max_horizontal = 3.0f;
    private float pre_launch_rotate_max_vertical = 20.0f;

    private float initial_hor_rotation;
    private float initial_ver_rotation;

    private bool isLaunched;

    // Use this for initialization
    void Start () {
        this.isLaunched = false;
        this.initial_hor_rotation = this.transform.rotation.x;
        this.initial_ver_rotation = this.transform.rotation.y;
        this.timer.text = "30:00";
        this.timer.fontSize = 20;
    }
	
	// Update is called once per frame
	void Update () {
        

        if (this.isLaunched)
        {
            this.checkMonsterCollision();
            //this.checkTerrainCollision();
            this.updateTimer();
            this.checkTimer();
        }

        if (Input.GetKey(KeyCode.W))
        {
            transform.Rotate(Vector3.down, -this.turnSpeed * Time.deltaTime);
        }
        else if (Input.GetKey(KeyCode.S))
        {
            transform.Rotate(Vector3.down, this.turnSpeed * Time.deltaTime);
        }
        else if (Input.GetKey(KeyCode.A))
        {
            transform.Rotate(Vector3.right, this.turnSpeed * Time.deltaTime);
        }
        else if (Input.GetKey(KeyCode.D))
        {
            if (!this.isLaunched)
            {
                if( Math.Abs(transform.rotation.x + this.initial_hor_rotation) + this.turnSpeed * Time.deltaTime > this.pre_launch_rotate_max_horizontal)
                {
                    //transform.Rotate(Vector3.left, 0.0f);
                }
                else
                {
                    transform.Rotate(Vector3.left, this.turnSpeed * Time.deltaTime);
                }
            }
            else
            { 
                transform.Rotate(Vector3.left, this.turnSpeed * Time.deltaTime);
            }
        }
        else if (Input.GetKey(KeyCode.Space) && !this.isLaunched)
        {
            this.isLaunched = true;
        }

        if (isLaunched)
        {
            transform.Translate(Vector3.forward * rocketSpeed * Time.deltaTime);
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
        float newTime = (float)Convert.ToDouble(this.timer.text.Replace(':', '.')) - dTime;
        this.timer.text = newTime.ToString("F").Replace('.', ':');

        if ((float)Convert.ToDouble(this.timer.text.Replace(':', '.')) - dTime <= 5.0)
        {
            this.timer.color = Color.red;
        }
    }

    private void checkTimer()
    {
        if((float)Convert.ToDouble(this.timer.text.Replace(':', '.')) <= 0.0f)
        {
            SceneManager.LoadScene(SceneManager.GetActiveScene().name);
        }
    }

    private void checkMonsterCollision()
    {
        SphereCollider collider = this.monster_boundary.GetComponent<SphereCollider>();
        if (collider.bounds.Contains(this.transform.position))
        {
            SceneManager.LoadScene(SceneManager.GetActiveScene().name);
        }
    }

    /*private void checkTerrainCollision()
    {
        for(int i = 0; i < this.terrain_boundaries.transform.childCount; i++)
        {
            GameObject border = this.terrain_boundaries.transform.GetChild(i).gameObject;
            BoxCollider box = border.GetComponent<BoxCollider>();
            if (box.bounds.Contains(this.transform.position))
            {
                SceneManager.LoadScene(SceneManager.GetActiveScene().name);
            }
        }
    }*/
}