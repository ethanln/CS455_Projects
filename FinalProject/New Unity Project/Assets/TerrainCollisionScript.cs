using UnityEngine;
using UnityEngine.SceneManagement;
using System.Collections.Generic;

public class TerrainCollisionScript : MonoBehaviour {

    public GameObject explosion;

	// Use this for initialization
	void Start () {

	}
	
	// Update is called once per frame
	void Update () {
        
    }

    void OnTriggerEnter(Collider col)
    {
        if (col.gameObject.name == "missle_pivot")
        {
            //MisslePivotController.rocketSpeed = 2.0f;
            //SceneManager.LoadScene(SceneManager.GetActiveScene().name);
            MisslePivotController.isGameOver = true;
            MisslePivotController.isLoss = true;
        }
       
        if(col.gameObject.name == "bomb_prefab(Clone)")
        {
            Destroy(col.gameObject);
            GameObject exp = Instantiate(this.explosion, new Vector3(col.transform.position.x, col.transform.position.y - 0.6f, col.transform.position.z), col.transform.rotation) as GameObject;

            // disable collision events with bombs
            foreach (GameObject b in GameObject.FindGameObjectsWithTag("clone_bomb"))
            {
                Physics.IgnoreCollision(exp.GetComponent<Collider>(), b.GetComponent<Collider>());
            }

            // disable collision events with other explosions.
            foreach (GameObject b in GameObject.FindGameObjectsWithTag("bomb_explosion"))
            {
                Physics.IgnoreCollision(exp.GetComponent<Collider>(), b.GetComponent<Collider>());
            }
        }
    }
}
