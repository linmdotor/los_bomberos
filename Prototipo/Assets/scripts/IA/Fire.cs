﻿using UnityEngine;
using System.Collections;
using UnityEngine.Assertions;

public class Fire : MonoBehaviour {

    public float m_damegePerSecond = 1.0f;
    public float m_propagationTime = 2.0f;
    private float m_nextPropagation = 0.0f;
    private bool m_init = false;
    private EventFirefighterOnFire m_eventFirefighterOnFire  = new EventFirefighterOnFire();

	// Use this for initialization
	void Start () {
        init();
	}

    void init()
    {
        m_init = true;
        m_nextPropagation = m_propagationTime;
    }
	// Update is called once per frame
	void Update () {
        Assert.IsFalse(m_init);
        m_nextPropagation -= Time.deltaTime;
        if ( m_nextPropagation < 0.0f )
        {
            m_nextPropagation = m_propagationTime;
            //logica de propagación
        }
	}
    void OnTriggerEnter(Collider other) {
        Assert.IsFalse(m_init);
        //m_eventFirefighterOnFire.m_firefighter = other.;7
        if (other.gameObject.tag.Equals("Player"))
        {
            other.gameObject.SendMessage("OnFire");
        }
        else if (other.gameObject.tag.Equals("Water"))
        {
            //avisamos de que esta perdiendo vida, suponemos un componente life
            gameObject.SendMessage("OnDamage", other.gameObject.GetComponent<Damagable>().getDamage());
        }
        //m_eventFirefighterOnFire.SendEvent();
    }
    public void OnDead()
    {
        Assert.IsFalse(m_init);
        Destroy(gameObject);
    }
    
}