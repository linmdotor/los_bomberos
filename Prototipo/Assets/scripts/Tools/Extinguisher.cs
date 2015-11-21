using UnityEngine;
using System.Collections;

public class Extinguisher : MonoBehaviour {

    public Transform m_ShootPoint = null;
    public GameObject m_AoE = null;
    public GameObject m_Water = null;

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}

    //Funciones llamadas desde el input para activar y desactivar el extintor. Tanto collider como efecto.
    void startShooting()
    {
        m_AoE.SetActive(true);
        m_Water.SetActive(true);
    }
    void stopShooting()
    {
        m_AoE.SetActive(false);
        m_Water.SetActive(false);
    }
}
