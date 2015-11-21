using UnityEngine;
using System.Collections;

public class Character : MonoBehaviour {
    private string m_SuitType = null;
    private int m_DeathTime = 10;

	// Use this for initialization
	void Start () {
	    
	}
	
	// Update is called once per frame
	void Update () {
	
	}
    //Las opciones de traje son 2: Ignifugo y Normal.
    void setSuitType(string suit){
        m_SuitType = suit;
        if (m_SuitType == "Ignifugo")
        {
            m_DeathTime += 10;
        }
    }

    void isDead()
    {
        if (m_DeathTime < 0)
        {
            this.SendMessage(this.name);
        }
    }
}
