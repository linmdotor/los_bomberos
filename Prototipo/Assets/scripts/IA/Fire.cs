using UnityEngine;
using System.Collections;
using UnityEngine.Assertions;

public class Fire : MonoBehaviour {

    public float m_damegePerSecond = 1.0f;

    private bool m_init = false;
    private EventFirefighterOnFire m_eventFirefighterOnFire  = new EventFirefighterOnFire();
	// Use this for initialization
	void Start () {
        init();
	}

    void init()
    {
        m_init = true;
    }
	// Update is called once per frame
	void Update () {
        Assert.IsFalse(m_init);
	}
    void OnTriggerEnter(Collider other) {
        m_eventFirefighterOnFire.SendEvent();
    }
}
