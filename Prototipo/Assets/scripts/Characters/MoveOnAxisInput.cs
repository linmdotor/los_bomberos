using UnityEngine;
using System.Collections;

using GamepadInput;

public class MoveOnAxisInput : MonoBehaviour {

    public string nController = "One";

    GamePad.Index mIndice;

    public float speed = 2.0f;

    void Start()
    {
        mIndice = GamePad.Index.One;
    }
	
	// Update is called once per frame
	void Update () {

        transform.position += (Vector3.right * GamePad.GetAxis(GamePad.Axis.LeftStick, mIndice).x + Vector3.forward * GamePad.GetAxis(GamePad.Axis.LeftStick, mIndice).y) * speed * Time.deltaTime;

	}
}
