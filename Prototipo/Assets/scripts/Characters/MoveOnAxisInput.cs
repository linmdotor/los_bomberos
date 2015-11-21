using UnityEngine;
using System.Collections;

public class MoveOnAxisInput : MonoBehaviour {

    public float speed = 2.0f;
    public string horizontalAxis = "Horizontal";
    public string verticalAxis = "Vertical";
	
	// Update is called once per frame
	void Update () {

        transform.position += (Vector3.right * Input.GetAxis(horizontalAxis) + Vector3.forward * Input.GetAxis(verticalAxis)) * Time.deltaTime;

	}
}
