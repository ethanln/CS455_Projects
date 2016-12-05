using UnityEngine;
using UnityEngine.SceneManagement;
using System.Collections;

public class TerrainCollisionScript : MonoBehaviour {

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
            MisslePivotController.rocketSpeed = 2.0f;
            SceneManager.LoadScene(SceneManager.GetActiveScene().name);
        }
       
        if(col.gameObject.name == "bomb_prefab(Clone)")
        {
            Destroy(col.gameObject);
        }
    }
}
