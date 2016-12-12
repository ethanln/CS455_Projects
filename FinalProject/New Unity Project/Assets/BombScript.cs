using UnityEngine;
using System.Collections;

public class BombScript : MonoBehaviour {

    public float bomb_speed;
    private float player_speed;

    // Use this for initialization
    void Start ()
    {
        this.player_speed = MisslePivotController.rocketSpeed;
        this.transform.parent = null;
    }
	
	// Update is called once per frame
	void Update () {
        transform.position += transform.forward * Time.deltaTime * (Mathf.Abs(player_speed) + bomb_speed);
    }
}
