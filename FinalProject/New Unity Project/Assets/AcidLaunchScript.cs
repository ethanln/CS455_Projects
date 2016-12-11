using UnityEngine;
using System.Collections;

public class AcidLaunchScript : MonoBehaviour {

    public GameObject acid_obj;
    public GameObject player;

    public float radius_monster_boundary;

    public float current_launch_delay;
    public float acid_launch_delay_limit;

	// Use this for initialization
	void Start () {
        this.current_launch_delay = 0.0f;
    }
	
	// Update is called once per frame
	void Update () {
        // check if game is over before any action is taken.
        if (MisslePivotController.isGameOver)
        {
            return;
        }

        if((this.player.transform.position - this.transform.position).magnitude <= this.radius_monster_boundary)
        {
            this.current_launch_delay += Time.deltaTime;
            if (this.current_launch_delay >= acid_launch_delay_limit)
            {
                this.current_launch_delay = 0.0f;
                GameObject obj = Instantiate(this.acid_obj, this.gameObject.transform.position, this.gameObject.transform.rotation) as GameObject;
                Physics.IgnoreCollision(obj.GetComponent<Collider>(), this.player.GetComponent<Collider>());
            }
        }
        else
        {
            this.current_launch_delay = 0;
        }
    }
}
