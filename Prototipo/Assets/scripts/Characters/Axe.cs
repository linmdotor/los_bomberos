using UnityEngine;
using System.Collections;
[RequireComponent(typeof(Damager))]
[RequireComponent(typeof(BoxCollider))]
public class Axe : MonoBehaviour {

    private BoxCollider m_boxCollider;
    private Damager m_damager;
    private Animator m_animator;

    private float currentTime;

	// Use this for initialization
	void Awake () {
        m_boxCollider = gameObject.GetComponent<BoxCollider>();
        m_damager = gameObject.GetComponent<Damager>();
        m_animator = gameObject.GetComponentInChildren<Animator>();
	}
	
	// Update is called once per frame
	void Update () {
        currentTime -= Time.deltaTime;
        /*if (m_boxCollider.enabled && currentTime < 0.0)
        {
            currentTime = 0.0f;
            m_boxCollider.enabled = false;
        }*/
	}

    void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.tag.Equals("Door"))
        {
            other.gameObject.SendMessage("OnDamage", m_damager.m_damage);
            m_boxCollider.enabled = false;
        }
    }
    public void activeAxe(float seconds)
    {
        currentTime = seconds;
        m_boxCollider.enabled = true;
        m_animator.SetTrigger("Attack");
    }
}
