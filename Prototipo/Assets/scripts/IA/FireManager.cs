using UnityEngine;
using System.Collections;

public class FireManager : MonoBehaviour {

    private Map m_map;

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
    public void firePropagation(Vector3 position, float damegePerPropagationTime, Fire fire)
    {
        uint xMin = ((uint)(position.x / m_map.m_xSize)-1);
        uint zMin = ((uint)(position.z / m_map.m_zSize)-1);
        if (xMin < 0) xMin = 0;
        if (zMin < 0) zMin = 0;

        uint xMax = xMin+1;
        uint zMax = zMin+1;
        if (xMax >= m_map.m_xCell) xMax = m_map.m_xCell-1;
        if (zMax >= m_map.m_xCell) zMax = m_map.m_zCell - 1;
        for (uint x = xMin; x <= xMax; ++x)
        {
            for (uint z = zMin; z <= zMax; ++z)
            {
                if (m_map.m_ObjectsMap[x][z] != null)
                {
                    if (m_map.m_ObjectsMap[x][z].isAlive())
                    {
                        bool dead = m_map.m_ObjectsMap[x][z].OnDamage(damegePerPropagationTime);
                        if (dead)
                        {
                            m_map.m_FireMap[x][z] = true;
                            Instantiate(fire, new Vector3(x * m_map.m_xSize, position.y, z * m_map.m_zSize), fire.transform.rotation);
                        }
                    }
                }
                else if (!m_map.m_FireMap[x][z])
                {
                    m_map.m_FireMap[x][z] = true;
                    Instantiate(fire, new Vector3(x * m_map.m_xSize, position.y, z * m_map.m_zSize), fire.transform.rotation);
                }
            }
        }

    }


}
