using UnityEngine;
using System.Collections;
using UnityEngine.Assertions;

[RequireComponent(typeof(BoxCollider))]
[RequireComponent(typeof(AudioSource))]
public class Fire : MonoBehaviour {

    public float m_damegePerPropagationTime = 1.0f;
    public float m_propagationTime = 2.0f;
    public bool m_canBePropagated = true;
    public GameObject m_smokeParticle;
    private float m_nextPropagation = 0.0f;
    private bool m_init = false;
    //private EventFirefighterOnFire m_eventFirefighterOnFire  = new EventFirefighterOnFire();

    private FireManager fireManager;

	// Use this for initialization
	void Start () {
        init();
        fireManager = FireManager.m_instance;
        fireManager.addFire(transform.position);
	}

    void init()
    {
        AudioSource aud = gameObject.GetComponent<AudioSource>();
        aud.Play();
        m_init = true;
        m_nextPropagation = m_propagationTime;
    }
	// Update is called once per frame
	void Update () {
        Assert.IsTrue(m_init);
        m_nextPropagation -= Time.deltaTime;
        if (m_canBePropagated && m_nextPropagation < 0.0f)
        {
            m_nextPropagation = m_propagationTime;
            fireManager.firePropagation(transform.position, m_damegePerPropagationTime);
            //logica de propagación
        }
	}
    void OnTriggerEnter(Collider other) {
        Assert.IsTrue(m_init);
        //m_eventFirefighterOnFire.m_firefighter = other.;7
        if (other.gameObject.tag.Equals("Player"))
        {
            other.gameObject.SendMessage("OnFire");
        }
    }
    void OnTriggerStay(Collider other)
    {
        if (other.gameObject.tag.Equals("Water"))
        {
            gameObject.SendMessage("OnDamage", other.gameObject.GetComponent<Damager>().getDamage()*Time.fixedDeltaTime);
            Instantiate(m_smokeParticle, transform.position, transform.rotation);
        }

        if(other.gameObject.tag.Equals("Explosive"))
        {
            other.SendMessage("OnDamage", other.gameObject.GetComponent<Damager>().getDamage() * Time.fixedDeltaTime);
        }
    }
    public void OnDead()
    {
        Assert.IsTrue(m_init);
        fireManager.removeFire(transform.position);
        Destroy(gameObject);
    }
    
}
