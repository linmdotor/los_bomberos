using UnityEngine;
using System.Collections;

public class NotificationManager : MonoBehaviour{
    public static NotificationManager m_instance = null;

    public GameObject m_HelpBurning = null;
    public GameObject m_HelpNPC = null;
    public GameObject m_HelpFire = null;
    private GameObject[] m_Players = null;

    private GameObject[][] m_BurningNotifications;

	// Use this for initialization
	void Start () {
        if (m_instance == null)
        {
            m_instance = this;
            DontDestroyOnLoad(m_instance);
        }
        else if (m_instance != this)
        {
            Destroy(this.gameObject);
        }
	}
	
	// Update is called once per frame
	void Update () {
        if(GameManager.m_instance.m_Init && m_Players == null && m_BurningNotifications == null){
            m_Players = GameManager.m_instance.getPlayers();
            m_BurningNotifications = new GameObject[m_Players.Length][];
            for (int i = 0; i < m_Players.Length; ++i)
            {
                m_BurningNotifications[i] = new GameObject[m_Players.Length];
            }
        }
        if(m_Players != null && m_BurningNotifications != null)
        {
            foreach (GameObject player in m_Players)
            {
                if (player.GetComponent<Character>().getOnFire())
                {
                    foreach (GameObject nonBurning in m_Players)
                    {

                        int id1 = (int)player.GetComponent<Character>().getID();
                        int id2 = (int)nonBurning.GetComponent<Character>().getID();

                        //Crea una notifiación de: Personaje ardiendo| Para los demas personajes
                        if (player != nonBurning && !(nonBurning.GetComponent<Character>().getOnFire())
                            && m_BurningNotifications[id1][id2] == null)
                        {
                            Vector3 position = new Vector3(
                                nonBurning.transform.position.x,
                                nonBurning.transform.position.y + 2,
                                nonBurning.transform.position.z + 1);
                            m_BurningNotifications[id1][id2] = (GameObject)Instantiate(m_HelpBurning, position, Quaternion.identity);
                        }

                        //Actualiza la posición de las notificaciones
                        if (!(nonBurning.GetComponent<Character>().getOnFire()))
                        {
                            m_BurningNotifications[id1][id2].transform.position = new Vector3(
                                nonBurning.transform.position.x,
                                nonBurning.transform.position.y + 2,
                                nonBurning.transform.position.z + 1);
                            m_BurningNotifications[id1][id2].transform.LookAt(m_Players[(int)player.GetComponent<Character>().getID()].transform);
                        }
                    }
                }
            }
        }
    }
}
