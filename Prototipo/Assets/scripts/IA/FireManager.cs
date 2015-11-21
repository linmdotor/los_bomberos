using UnityEngine;
using System.Collections;

public class FireManager : MonoBehaviour {

    Map map;

    public static FireManager m_instance;

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
	
	}


}
