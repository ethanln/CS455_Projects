using UnityEngine;
using System.Collections;
using UnityEngine.UI;
using System;

public class MonsterCollision : MonoBehaviour {

    public float max_hp;
    public float current_hp;

    public Text monster_hp_display;

    public static bool monsterIsDead = false;

    private const string monster_header = "Monster: ";

	// Use this for initialization
	void Start () {
        this.updateMonsterHPHeader();
    }
	
	// Update is called once per frame
	void Update () {
	    
	}

    void OnTriggerEnter(Collider col)
    {

        if (col.gameObject.name == "bomb_explosion(Clone)")
        {
            this.current_hp -= 3.0f;
            this.updateMonsterHPHeader();
        }

        if(this.current_hp <= 0.0f)
        {
            Destroy(this.transform.gameObject);
            MonsterCollision.monsterIsDead = true;
            MisslePivotController.isGameOver = true;
            MisslePivotController.isVictory = true;
        }
    }

    private void updateMonsterHPHeader()
    {
        string percentage = Convert.ToString(100 * (this.current_hp / this.max_hp)) + "%";
        this.monster_hp_display.text = monster_header + percentage;
    }
}
