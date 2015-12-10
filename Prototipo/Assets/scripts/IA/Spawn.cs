using UnityEngine;
using System.Collections;

public class Spawn : MonoBehaviour {

    public GameObject spawn;
    public float remainingTimeToSpawn = 1.0f;
    public float m_timeBeforePropagation = 2.0f;

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
        remainingTimeToSpawn -= Time.deltaTime;
        if (remainingTimeToSpawn < 0.0f)
        {
            spawn = (GameObject)Instantiate(spawn, transform.position, transform.rotation);
            if (spawn.GetComponent<Fire>() != null)
				spawn.GetComponent<Fire>().m_propagationTime = m_timeBeforePropagation;
            enabled = false;
        }
	}
}
