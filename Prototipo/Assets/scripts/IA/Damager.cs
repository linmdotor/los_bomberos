using UnityEngine;
using System.Collections;

public class Damager : MonoBehaviour {

    public float m_damage = 10.0f;
	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}

    public float getDamage()
    {
        return m_damage;
    }
}
