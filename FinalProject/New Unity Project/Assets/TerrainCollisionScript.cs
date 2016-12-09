using UnityEngine;
using UnityEngine.SceneManagement;
using System.Collections.Generic;

public class TerrainCollisionScript : MonoBehaviour {

    public GameObject explosion;
    private List<GameObject> active_explosions;

	// Use this for initialization
	void Start () {
        this.active_explosions = new List<GameObject>();
	}
	
	// Update is called once per frame
	void Update () {
        foreach (GameObject active_explosion in this.active_explosions)
        {
            if (active_explosion.transform.localScale.x > 2.5f ||
                active_explosion.transform.localScale.y > 2.5f ||
                active_explosion.transform.localScale.z > 2.5f)
            {
                Destroy(active_explosion);
                this.active_explosions.RemoveAt(this.active_explosions.IndexOf(active_explosion));
            }
        }
    }

    void OnTriggerEnter(Collider col)
    {
        if (col.gameObject.name == "missle_pivot")
        {
            MisslePivotController.rocketSpeed = 2.0f;
            SceneManager.LoadScene(SceneManager.GetActiveScene().name);
        }
       
        if(col.gameObject.name == "bomb_prefab(Clone)")
        {
            Destroy(col.gameObject);
            this.active_explosions.Add(Instantiate(this.explosion, new Vector3(col.transform.position.x, col.transform.position.y - 0.6f, col.transform.position.z), col.transform.rotation) as GameObject);
        }
    }
}
