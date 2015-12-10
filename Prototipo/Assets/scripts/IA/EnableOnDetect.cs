using UnityEngine;
using UnityEngine.Assertions;
using System.Collections;
public class EnableOnDetect : MonoBehaviour {

    public string m_tag = "Player";
    public GameObject m_objectToEnable;

	// Use this for initialization
	void Start () {
        BoxCollider boxAux = GetComponent<BoxCollider>();
        SphereCollider sphereAux = GetComponent<SphereCollider>();
        Assert.IsTrue(boxAux != null || sphereAux != null);
        if (boxAux != null)
        {
            boxAux.isTrigger = true;
        }
        else
        {
            sphereAux.isTrigger = true;
        }
	}
	
	// Update is called once per frame
	void Update () {
	
	}

    void OnTriggerEnter(Collider other)
    {
        //m_eventFirefighterOnFire.m_firefighter = other.;7
        if (other.gameObject.tag.Equals(m_tag))
        {
            m_objectToEnable.SetActive(true);
            this.enabled = false;
        }
    }
}
