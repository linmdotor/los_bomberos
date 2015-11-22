using UnityEngine;
using System.Collections;

public class Extinguisher : MonoBehaviour {

    public Transform m_ShootPoint = null;
    public GameObject m_AoE = null;
    public GameObject m_Water = null;

    private bool isActive = false;

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}

    //Funciones llamadas desde el input para activar y desactivar el extintor. Tanto collider como efecto.
    void startShooting()
    {
        //if is not active, start the fire hose sound loop
        if (!isActive)
        {
            isActive = true;
            AudioSource aud = gameObject.GetComponent<AudioSource>();
            aud.Play();
            
        }

        m_AoE.SetActive(true);
        m_Water.SetActive(true);
    }
    void stopShooting()
    {

        //finish the fire hose sound loop if is active
        if (isActive)
        {
            AudioSource aud = gameObject.GetComponent<AudioSource>();
            aud.Stop();
            isActive = false;
        }

        m_AoE.SetActive(false);
        m_Water.SetActive(false);
    }
}
