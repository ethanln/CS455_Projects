using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class LevelTitleAnimateScript : MonoBehaviour {

    private float current_scale;
    private Image img;

    // Use this for initialization
    void Start () {
        this.img = this.GetComponent<Image>();
        this.current_scale = 1.0f;
    }
	
	// Update is called once per frame
	void Update () {

        this.current_scale -= (Time.deltaTime * 0.1f);
        this.transform.localScale = new Vector3(current_scale, current_scale, current_scale);

        this.img.CrossFadeAlpha(0.0f, 0.3f, false);

    }
}
