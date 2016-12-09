using UnityEngine;
using System.Collections;

public class ExplosionBehavior : MonoBehaviour {

    float explosion_speed = 1.5f;
	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
        this.transform.localScale = new Vector3(this.transform.localScale.x + 0.005f, this.transform.localScale.y + 0.005f, this.transform.localScale.z + 0.005f);
        if (this.transform.localScale.x > 2.5f ||
                this.transform.transform.localScale.y > 2.5f ||
                this.transform.transform.localScale.z > 2.5f)
        {
            Destroy(this.transform.gameObject);
        }
    }
}
