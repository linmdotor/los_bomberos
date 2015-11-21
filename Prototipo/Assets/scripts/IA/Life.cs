using UnityEngine;
using System.Collections;

public class Life : MonoBehaviour {

    public float m_maxLife = 100.0f;
    private float m_currentLife;
	// Use this for initialization
	void Start () {
        m_currentLife = m_maxLife;	    
	}
	
	// Update is called once per frame
	void Update () {
	
	}
    public bool OnDamage(float damage)
    {
        m_currentLife -= damage;
        if (m_currentLife <= 0.0f)
        {
            gameObject.SendMessage("OnDead");
            m_currentLife = 0.0f;
            return true;
        }
        return false;
    }
    public bool isAlive()
    {
        return m_currentLife > 0.0f;
    }

    public float getLife()
    {
        return m_currentLife;
    }

    public float getMaxLife()
    {
        return m_maxLife;
    }
}
