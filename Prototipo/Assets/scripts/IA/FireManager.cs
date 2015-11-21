using UnityEngine;
using System.Collections;

public class FireManager : MonoBehaviour {

    private Map m_map;

    public static FireManager m_instance = null;
    public GameObject fire;

	// Use this for initialization
	void Start () {
        if (m_instance == null)
        {
            m_instance = this;
            DontDestroyOnLoad(m_instance);
            m_map = gameObject.GetComponent<Map>();
        }
        else if (m_instance != this)
        {
            Destroy(this.gameObject);
        }
	}
	
	// Update is called once per frame
	void Update () {
	
	}
    public void addFire(Vector3 position)
    {
        int x = (int)(position.x / m_map.m_xSize);
        int z = (int)(position.z / m_map.m_zSize);
        m_map.m_FireMap[x][z] = true;
    }
    public void firePropagation(Vector3 position, float damegePerPropagationTime)
    {
        int xMin = ((int)(position.x / m_map.m_xSize) - 1);
        int zMin = ((int)(position.z / m_map.m_zSize) - 1);
        if (xMin < 0) xMin = 0;
        if (zMin < 0) zMin = 0;

        int xMax = xMin + 2;
        int zMax = zMin + 2;
        if (xMax >= m_map.m_xCell) xMax = m_map.m_xCell-1;
        if (zMax >= m_map.m_xCell) zMax = m_map.m_zCell - 1;
        for (int x = xMin; x <= xMax; ++x)
        {
            for (int z = zMin; z <= zMax; ++z)
            {
                if (m_map.m_ObjectsMap[x][z] != null)
                {
                    if (m_map.m_ObjectsMap[x][z].isAlive())
                    {
                        bool dead = m_map.m_ObjectsMap[x][z].OnDamage(damegePerPropagationTime);
                        if (dead)
                        {
                            m_map.m_FireMap[x][z] = true;
                            Instantiate(fire, new Vector3(x * m_map.m_xSize + m_map.m_xSize * 0.5f, position.y, z * m_map.m_zSize + m_map.m_zSize*0.5f), fire.transform.rotation);
                            return;
                        }
                    }
                }
                else if (!m_map.m_FireMap[x][z])
                {
                    m_map.m_FireMap[x][z] = true;
                    Instantiate(fire, new Vector3(x * m_map.m_xSize + m_map.m_xSize * 0.5f, position.y, z * m_map.m_zSize + m_map.m_zSize * 0.5f), fire.transform.rotation);
                    return;
                }
            }
        }

    }


}
