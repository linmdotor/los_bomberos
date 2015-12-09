using UnityEngine;
using System.Collections;

public class HelpNotifications : MonoBehaviour {
    
    public GameObject m_HelpBurning = null;
    public GameObject m_HelpNPC = null;
    public GameObject m_HelpFire = null;
    public GameObject[] m_Players = null;

    private GameObject[][] m_BurningNotifications;

	// Use this for initialization
	void Start () {
        m_BurningNotifications = new GameObject[m_Players.Length][];
        for (int i = 0; i < m_Players.Length; ++i)
        {
            m_BurningNotifications[i] = new GameObject[m_Players.Length];
        }
	}
	
	// Update is called once per frame
	void Update () {
        //Crea una notifiación de: Personaje ardiendo| Para los demas personajes
        foreach (GameObject player in m_Players)
        {
            if (player.GetComponent<Character>().getOnFire())
            {
                foreach (GameObject nonBurning in m_Players)
                {
                    int id1 = (int)player.GetComponent<Character>().getID();
                    int id2 = (int)nonBurning.GetComponent<Character>().getID();
                    if (player != nonBurning && m_BurningNotifications[id1][id2] == null)
                    {
                        Vector3 position = new Vector3(
                            nonBurning.transform.position.x,
                            nonBurning.transform.position.y + 2,
                            nonBurning.transform.position.z + 1);
                        m_BurningNotifications[id1][id2] = (GameObject)Instantiate(m_HelpBurning, position, Quaternion.identity);
                    }
                }
            }
        }

        //Actualiza la posición de las notificaciones
        foreach (GameObject player in m_Players)
        {
            if (player.GetComponent<Character>().getOnFire())
            {
                foreach (GameObject nonBurning in m_Players)
                {
                    if (!(nonBurning.GetComponent<Character>().getOnFire()))
                    {
                        int id1 = (int)player.GetComponent<Character>().getID();
                        int id2 = (int)nonBurning.GetComponent<Character>().getID();
                        m_BurningNotifications[id1][id2].transform.position = new Vector3(
                            nonBurning.transform.position.x,
                            nonBurning.transform.position.y + 2,
                            nonBurning.transform.position.z + 1);
                        m_BurningNotifications[id1][id2].transform.LookAt(m_Players[(int)player.GetComponent<Character>().getID()].transform);
                    }
                }
            }
        }
        //Borra notificaciones si mueres o eres apagado
    }
}
