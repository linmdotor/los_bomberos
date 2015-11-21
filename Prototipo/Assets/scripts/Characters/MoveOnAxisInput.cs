using UnityEngine;
using System.Collections;

using GamepadInput;

public class MoveOnAxisInput : MonoBehaviour {

    public string nController = "One";
   
    public float speed = 2.0f;
	
	// Update is called once per frame
	void Update () {

        transform.position += (Vector3.right * GamePad.GetAxis(GamePad.Axis.LeftStick, GamePad.Index.One).x + Vector3.up * GamePad.GetAxis(GamePad.Axis.LeftStick, GamePad.Index.One).y) * Time.deltaTime;

	}
}
