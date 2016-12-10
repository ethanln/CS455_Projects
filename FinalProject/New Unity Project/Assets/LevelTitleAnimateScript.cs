using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class LevelTitleAnimateScript : MonoBehaviour {

    public float FadeRate;

    private float current_scale;
    private float targetAlpha;
    private Image img;

    // Use this for initialization
    void Start () {
        this.img = this.GetComponent<Image>();

        this.current_scale = 1.0f;
        this.targetAlpha = this.img.color.a;
    }
	
	// Update is called once per frame
	void Update () {

        this.current_scale -= (Time.deltaTime * 0.1f);
        this.transform.localScale = new Vector3(current_scale, current_scale, current_scale);

        this.img.CrossFadeAlpha(0.0f, 1.0f, false);

        /*Color curColor = this.img.color;
        float alphaDiff = Mathf.Abs(curColor.a - this.targetAlpha);
        if (alphaDiff >= 0.0001f)
        {
            curColor.a = Mathf.Lerp(curColor.a, targetAlpha, this.FadeRate * Time.deltaTime);
            this.img.color = curColor;
        }*/
    }
}
