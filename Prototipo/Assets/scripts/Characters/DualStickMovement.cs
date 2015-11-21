using UnityEngine;
using System.Collections;

using GamepadInput;

public class DualStickMovement : MonoBehaviour
{
    static int nController = 1;
    GamePad.Index mIndice;

    public float speed = 5.0f;

    void Start()
    {      
        mIndice = (GamePad.Index)nController;
        ++nController;
    }

    // Update is called once per frame
    void Update()
    {
        Vector3 leftStickAxis = (Vector3.right * GamePad.GetAxis(GamePad.Axis.LeftStick, mIndice).x + Vector3.forward * GamePad.GetAxis(GamePad.Axis.LeftStick, mIndice).y);
        transform.position += leftStickAxis * speed * Time.deltaTime;
        Vector3 lookDir = (Vector3.right * GamePad.GetAxis(GamePad.Axis.RightStick, mIndice).x + Vector3.forward * GamePad.GetAxis(GamePad.Axis.RightStick, mIndice).y);

        if (lookDir.sqrMagnitude > 0.0f)
        {
            transform.rotation = Quaternion.LookRotation(lookDir, Vector3.up);
        }
        
    }
}