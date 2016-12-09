using UnityEngine;
using System.Collections;

public class TerrainScript : MonoBehaviour {

    public GameObject plane;
    public GameObject bomb;

    private float bomb_delay;
    private bool isLaunched;

    // Use this for initialization
    void Start () {
        this.isLaunched = false;
        this.bomb_delay = 0.0f;
        this.bomb.transform.parent = null;
    }
	
	// Update is called once per frame
	void Update () {
        if (this.isLaunched)
        {
            this.bomb_delay += Time.deltaTime;
        }

        if (Input.GetKey(KeyCode.Space) && !this.isLaunched)
        {
            this.isLaunched = true;
        }
        else if (Input.GetKey(KeyCode.Space) && this.isLaunched)
        {
            if (this.bomb_delay >= 0.2f)
            {   
                this.bomb_delay = 0.0f;
                // create bomb object
                GameObject obj = Instantiate(this.bomb, this.plane.transform.position, this.plane.transform.rotation) as GameObject;

                // disable collision events for all clone bombs
                foreach (GameObject b in GameObject.FindGameObjectsWithTag("clone_bomb"))
                {
                    Physics.IgnoreCollision(obj.GetComponent<Collider>(), b.GetComponent<Collider>());
                }

                // disable collision events for all explosions
                foreach (GameObject b in GameObject.FindGameObjectsWithTag("bomb_explosion"))
                {
                    Physics.IgnoreCollision(obj.GetComponent<Collider>(), b.GetComponent<Collider>());
                }

                // disable collision events for plane
                foreach (Collider col in this.plane.transform.parent.GetComponents<Collider>())
                {
                    Physics.IgnoreCollision(obj.GetComponent<Collider>(), col);
                }
            }
        }
    }
}
