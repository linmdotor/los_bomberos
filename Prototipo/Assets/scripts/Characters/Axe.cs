using UnityEngine;
using System.Collections;
[RequireComponent(typeof(Damager))]
[RequireComponent(typeof(BoxCollider))]
[RequireComponent(typeof(AudioSource))]
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
            //calcula la vida que tiene y hace un sonido más fuerte cuanta menos vida le quede
            float current_life = other.GetComponent<Life>().getLife();
            if(current_life >= other.GetComponent<Life>().getMaxLife()/2.0)
            {
                AudioSource[] aud = gameObject.GetComponents<AudioSource>();
                aud[1].PlayOneShot(aud[1].clip);
            }
            else
            {
                AudioSource[] aud = gameObject.GetComponents<AudioSource>();
                aud[2].PlayOneShot(aud[2].clip);
            }


            other.gameObject.SendMessage("OnDamage", m_damager.m_damage);
            m_boxCollider.enabled = false;
        }
    }
    public void activeAxe(float seconds)
    {
        AudioSource[] aud = gameObject.GetComponents<AudioSource>();
        aud[0].Play();// PlayOneShot(aud[0].clip);
        currentTime = seconds;
        m_boxCollider.enabled = true;
        m_animator.SetTrigger("Attack");
    }
}
