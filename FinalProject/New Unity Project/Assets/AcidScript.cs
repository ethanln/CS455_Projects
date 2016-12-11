using UnityEngine;
using UnityEngine.SceneManagement;

public class AcidScript : MonoBehaviour
{

    public float life_span;
    public float acid_speed;
    private Vector3 target;
    private Vector3 prev_pos;

    // Use this for initialization
    void Start()
    {
        this.prev_pos = this.transform.position;
        foreach (GameObject b in GameObject.FindGameObjectsWithTag("Player"))
        {
            this.target = b.transform.position;
            break;
        }
    }

    // Update is called once per frame
    void Update()
    {
        this.life_span -= Time.deltaTime;

        float dx = this.transform.position.x - this.prev_pos.x;
        float dy = this.transform.position.y - this.prev_pos.y;
        float dz = this.transform.position.z - this.prev_pos.z;

        this.target.x += dx;
        this.target.y += dy;
        this.target.z += dz;

        float step = acid_speed * Time.deltaTime;
        transform.position = Vector3.MoveTowards(this.transform.position, this.target, step);


        if (this.life_span <= 0.0f)
        {
            Destroy(this.gameObject);
        }
    }

    void OnTriggerEnter(Collider col)
    {
        if(col.tag == "Player"
            && !MisslePivotController.isGameOver
            && !MisslePivotController.isLoss
            && !MisslePivotController.isVictory)
        {
            MisslePivotController.isGameOver = true;
            MisslePivotController.isLoss = true;
        }
        else
        {
            Destroy(this.gameObject);
        }
    }
}
