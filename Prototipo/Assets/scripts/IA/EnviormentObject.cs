using UnityEngine;
using System.Collections;
[RequireComponent(typeof(BoxCollider))]
[RequireComponent(typeof(Life))]
public class EnviormentObject : MonoBehaviour {

    private BoxCollider m_boxCollider;
	// Use this for initialization
	void Start () {
        m_boxCollider = gameObject.GetComponent<BoxCollider>();
        FindObjectOfType<Map>().addObjectToMap(m_boxCollider.bounds.min, m_boxCollider.bounds.max, gameObject.GetComponent<Life>());
	}
	
	// Update is called once per frame
	void Update () {
	
	}
}
