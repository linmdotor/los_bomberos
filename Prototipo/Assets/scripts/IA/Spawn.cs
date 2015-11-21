using UnityEngine;
using System.Collections;

public class Spawn : MonoBehaviour {

    public GameObject spawn;
    public float remainingTimeToSpawn = 1.0f;

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
        remainingTimeToSpawn -= Time.deltaTime;
        if (remainingTimeToSpawn < 0.0f)
        {
            Instantiate(spawn, transform.position, transform.rotation);
            enabled = false;
        }
	}
}
