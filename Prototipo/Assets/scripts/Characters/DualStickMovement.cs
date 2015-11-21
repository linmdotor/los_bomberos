using UnityEngine;
using System.Collections;

using GamepadInput;

public class DualStickMovement : MonoBehaviour
{
    private Rigidbody rb;
    static int mIndice = 1;
    GamePad.Index numController;

    private float speed = 5.0f;

    void setSpeed(float s)
    {
        speed = s;
    }

    void Start()
    {
        rb = GetComponent<Rigidbody>();
        numController = (GamePad.Index)mIndice;
        ++mIndice;
    }

    void FixedUpdate()
    {
        rb.velocity = vector
    }

    // Update is called once per frame
    void Update()
    {   
        //Hacha

        if (Input.GetKeyDown(KeyCode.Space) || GamePad.GetButtonDown(GamePad.Button.B, numController)) {
            gameObject.SendMessage("useTool");
        }

        //Movemos al personaje
        Vector3 leftStickAxis = (Vector3.right * GamePad.GetAxis(GamePad.Axis.LeftStick, numController).x + Vector3.forward * GamePad.GetAxis(GamePad.Axis.LeftStick, numController).y);
        transform.position += leftStickAxis * speed * Time.deltaTime;

        //Orientamos al personaje
        Vector3 lookDir = (Vector3.right * GamePad.GetAxis(GamePad.Axis.RightStick, numController).x + Vector3.forward * GamePad.GetAxis(GamePad.Axis.RightStick, numController).y);
        if (lookDir.sqrMagnitude > 0.0f) {
            transform.rotation = Quaternion.LookRotation(lookDir, Vector3.up);
            gameObject.BroadcastMessage("startShooting");
        } else {
            gameObject.BroadcastMessage("stopShooting");
        }
        
    }

}